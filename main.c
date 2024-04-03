#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 40000

struct contato
{
    char *nome;
    char *tel;
    char *email;
};

struct lista
{
    struct contato *contato;
    struct lista *prox;
};

struct contato *criaContato(char *nome, char *tel, char *email)
{
    struct contato *novo = (struct contato *)malloc(sizeof(struct contato));
    if (novo == NULL)
    {
        printf("Erro ao alocar memoria para novo contato.\n");
        exit(1);
    }
    novo->nome = strdup(nome);
    novo->tel = strdup(tel);
    novo->email = strdup(email);
    return novo;
}

int concatenacao(char c[])
{
    int chave = 0, i = 0;
    while (c[i] != '\0')
    {
        chave += c[i];
        i++;
    }
    return chave % TABLE_SIZE;
}

typedef struct lista *tabelaHash[TABLE_SIZE];

void inicializarTabela(tabelaHash tabela)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        tabela[i] = NULL;
    }
}

double hash(int chave)
{
    return (chave * 0.2) / TABLE_SIZE;
}

void inserirContato(tabelaHash tabela, struct contato *contato)
{
    int chave = concatenacao(contato->nome);
    int posicao = hash(chave) * TABLE_SIZE;

    struct lista *novoContato = (struct lista *)malloc(sizeof(struct lista));
    novoContato->contato = contato;
    novoContato->prox = NULL;

    if (tabela[posicao] == NULL)
    {
        tabela[posicao] = novoContato;
    }
    else
    {
        struct lista *atual = tabela[posicao];
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novoContato;
    }
}

struct contato *buscarContato(tabelaHash tabela, char *nome)
{
    int chave = concatenacao(nome);
    int posicao = hash(chave) * TABLE_SIZE;

    struct lista *atual = tabela[posicao];
    while (atual != NULL)
    {
        if (strcmp(atual->contato->nome, nome) == 0)
        {
            return atual->contato;
        }
        atual = atual->prox;
    }

    return NULL; // Contato não encontrado
}

void removerContato(tabelaHash tabela, char *nome)
{
    int chave = concatenacao(nome);
    int posicao = hash(chave) * TABLE_SIZE;

    struct lista *atual = tabela[posicao];
    struct lista *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->contato->nome, nome) == 0)
        {
            if (anterior == NULL)
            {
                tabela[posicao] = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual->contato->nome);
            free(atual->contato->tel);
            free(atual->contato->email);
            free(atual->contato);
            free(atual);

            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

void adicionarContatosArquivo(tabelaHash tabela, char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char nome[100], tel[20], email[100];

    while (fscanf(arquivo, "Nome: %[^\n]\nTelefone: %[^\n]\nEmail: %[^\n]\n\n", nome, tel, email) == 3)
    {
        // Remover o '-' do telefone
        for (char *c = tel; *c != '\0'; c++)
        {
            if (*c == '-')
            {
                *c = ' ';
            }
        }

        // Remover o '\n' do email
        email[strcspn(email, "\n")] = '\0';

        inserirContato(tabela, criaContato(nome, tel, email));
    }

    fclose(arquivo);
}

void listarContatos(tabelaHash tabela)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct lista *atual = tabela[i];
        while (atual != NULL)
        {
            printf("\nNome: %s, \nTelefone: %s, \nEmail: %s\n", atual->contato->nome, atual->contato->tel, atual->contato->email);
            atual = atual->prox;
        }
    }
}

void limparTabela(tabelaHash tabela)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct lista *atual = tabela[i];
        while (atual != NULL)
        {
            struct lista *prox = atual->prox;
            free(atual->contato->nome);
            free(atual->contato->tel);
            free(atual->contato->email);
            free(atual->contato);
            free(atual);
            atual = prox;
        }
        tabela[i] = NULL;
    }
}

int main()
{
    tabelaHash tabela;
    inicializarTabela(tabela);

    adicionarContatosArquivo(tabela, "todosOsContatos.txt");

    int opcao;
    char nome[100], tel[20], email[100];

    do
    {
        printf("\n===== MENU =====\n");
        printf("1. Inserir contato\n");
        printf("2. Buscar contato\n");
        printf("3. Remover contato\n");
        printf("4. Listar contatos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Nome: ");
            scanf("%s", nome);
            printf("Telefone: ");
            scanf("%s", tel);
            printf("Email: ");
            scanf("%s", email);
            inserirContato(tabela, criaContato(nome, tel, email));
            break;
        case 2:
            printf("Nome: ");
            scanf(" %[^\n]", nome);
            struct contato *c = buscarContato(tabela, nome);
            if (c != NULL)
            {
                printf("\nContato encontrado - Nome: %s, \nTelefone: %s, \nEmail: %s\n", c->nome, c->tel, c->email);
            }
            else
            {
                printf("Contato nao encontrado.\n");
            }
            break;
        case 3:
            printf("Nome: ");
            scanf(" %[^\n]", nome);
            removerContato(tabela, nome);
            break;
        case 4:
            listarContatos(tabela);
            break;
        case 5:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }

    } while (opcao != 5);

    limparTabela(tabela);

    return 0;
}
