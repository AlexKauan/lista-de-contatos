#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 40000
//struct que contem as informações dos contatos
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
//Função que cria um contato, com nome, telefone e e-mail. 
//Ele aloca dinamicamente o contato e caso a alocação seja bem sucedida ele copia os dados do contato criando uma cópia com a função strdup e retorna o novo contato
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

//Função que calcula o valor da chave de um contato com base no seu nome.
int concatenacao(char c[])
{
    int chave = 0, i = 0;
    while (c[i] != '\0') // percorre toda a string e soma o valor de cada caractere para calcular a chave.
    {
        chave += c[i];
        i++;
    }
    return chave % TABLE_SIZE; //Após a soma ela retorna o módulo da divisão da chave pelo tamanho  da tabela que foi definida
}

// Definição do tipo de dados para a tabela hash
typedef struct lista *tabelaHash[TABLE_SIZE];

//Função para inicializar a tabela hash
void inicializarTabela(tabelaHash tabela)
{
    for (int i = 0; i < TABLE_SIZE; i++)// O loop percorre a tabela até o tamanho da tabela menos 1
    {
        tabela[i] = NULL;//para cada índice da tabela é colocado NULL
    }
}

//Função que calcula a posição que a chave será colocada
double hash(int chave)
{
    return (chave * 0.2) / TABLE_SIZE;//Multiplica a chave calculada na função "concatenacao" por 0.2 e depois divide pelo tamanho da tabela
}

//Função para inserir um contato na tabela hash
void inserirContato(tabelaHash tabela, struct contato *contato)
{
    int chave = concatenacao(contato->nome);
    int posicao = hash(chave) * TABLE_SIZE;

    // Aloca memória para o novo elemento da lista encadeada
    struct lista *novoContato = (struct lista *)malloc(sizeof(struct lista));
    novoContato->contato = contato;
    novoContato->prox = NULL;

     // Verifica se a posição na tabela é NULL, se for, então um contato pode ser inserido
    if (tabela[posicao] == NULL)
    {
        tabela[posicao] = novoContato;
    }
    else //Ele procura uma posição para colocar sempre procurando o próximo indice na tabela
    {
        struct lista *atual = tabela[posicao];
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novoContato;
    }
}

//Função para buscar um contato na tabela 
struct contato *buscarContato(tabelaHash tabela, char *nome)
{
    int chave = concatenacao(nome);
    int posicao = hash(chave) * TABLE_SIZE;

    //Percorre a lista encadeda com base na posição que foi calculada
    struct lista *atual = tabela[posicao];
    while (atual != NULL)
    {
        if (strcmp(atual->contato->nome, nome) == 0) //compara os nomes da lista com o que está sendo procurado
        {
            return atual->contato; //Retorna o contato caso ele tenha sido encontrado
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
    //Percorre a lista com base na posição que foi calculada
    while (atual != NULL)
    {
       // Compara os nomes da lista com o que está sendo procurado e, se for igual, pega o ponteiro que apontava para ele e coloca para apontar para o próximo
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

            // Libera a memória alocada
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
    FILE *arquivo = fopen(nomeArquivo, "r"); //Abre um arquivo no mode de leitura
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char nome[100], tel[20], email[100];

    while (fscanf(arquivo, "Nome: %[^\n]\nTelefone: %[^\n]\nEmail: %[^\n]\n\n", nome, tel, email) == 3) // le o arquivo até três campos do arquivo(nome, telefone e e-amil)
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
    for (int i = 0; i < TABLE_SIZE; i++) //Loop percorre a tabela até o tamanho da tabela menos 1
    {
        struct lista *atual = tabela[i];
        while (atual != NULL)
        {
            printf("\nNome: %s, \nTelefone: %s, \nEmail: %s\n", atual->contato->nome, atual->contato->tel, atual->contato->email);
            atual = atual->prox;
        }
    }
}

//Função para limpar a memória que foi alocada
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
    tabelaHash tabela; //Variável para a tabela hash
    inicializarTabela(tabela);//Chamada da função para inicializar a tabela hash

    adicionarContatosArquivo(tabela, "todosOsContatos.txt"); //Chamada da função para adicionar os contatos no arquivo

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

    limparTabela(tabela); //Chamada da função para limpar a memória que foi alocada

    return 0;
}