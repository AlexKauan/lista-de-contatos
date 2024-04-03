#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10000

typedef struct Contato
{
    char nome[50];
    char telefone[15];
    char email[50];
    int ocupado;
    int removido;
} Contato;

/* typedef struct
{
    int chave;
    Contato contato;
} EntradaTabela; */

typedef struct Contato *tabelaHash[TABLE_SIZE];

void inicializarTabela(tabelaHash tabela)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        tabela[i] = NULL;
    }
}

int hash(int chave)
{
    return (int)(chave * 0.6180339887) * TABLE_SIZE % TABLE_SIZE;
}

void inserir(tabelaHash tabela, int chave, Contato contato)
{
    int posicao = hash(chave);
    int inicial = posicao;
    int inserido = 0;

    do
    {
        if (tabela[posicao]->nome)
        {
            tabela[posicao]->nome;

            tabela[posicao]->ocupado = 1;
            tabela[posicao]->removido = 0;
            inserido = 1;
            printf("Contato inserido com sucesso na posição %d\n", posicao);
        }
        else
        {
            posicao = (posicao + 1) % TABLE_SIZE;
        }
    } while (!inserido && posicao != inicial);

    if (!inserido)
    {
        printf("Não foi possível inserir o contato. Tabela cheia.\n");
    }
}

int buscar(tabelaHash tabela, int chave, Contato *contato)
{
    int posicao = hash(chave);
    int inicial = posicao;

    do
    {
        if (tabela[posicao]->ocupado && !tabela[posicao]->removido)
        {
            contato = tabela[posicao];
            printf("Contato encontrado na posição %d\n", posicao);
            return 1;
        }
        else if (!tabela[posicao]->ocupado)
        {
            printf("Contato não encontrado\n");
            return 0;
        }
        else
        {
            posicao = (posicao + 1) % TABLE_SIZE;
        }
    } while (posicao != inicial);

    printf("Contato não encontrado\n");
    return 0;
}

int remover(tabelaHash tabela, int chave)
{
    int posicao = hash(chave);
    int inicial = posicao;

    do
    {
        if (tabela[posicao]->ocupado && !tabela[posicao]->removido)
        {
            tabela[posicao]->removido = 1;
            printf("Contato removido com sucesso da posição %d\n", posicao);
            return 1;
        }
        else if (!tabela[posicao]->ocupado)
        {
            printf("Contato não encontrado\n");
            return 0;
        }
        else
        {
            posicao = (posicao + 1) % TABLE_SIZE;
        }
    } while (posicao != inicial);

    printf("Contato não encontrado\n");
    return 0;
}

int main()
{
    tabelaHash tabela;
    inicializarTabela(tabela);
     char nome[50], telefone[15], email[50];

    FILE *arquivo = fopen("todosOsContatos.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de contatos\n");
        return 1;
    }

    fscanf(arquivo,"Nome: %s\n Telefone: %s\n Email: %s\n",nome, telefone,email);
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        int chave;
       


        sscanf(linha, "%d %s %s %s", &chave, nome, telefone, email);
        Contato contato;
        strcpy(contato.nome, nome);
        printf("%s\n",nome);
        strcpy(contato.telefone, telefone);
        strcpy(contato.email, email);
        inserir(tabela, chave, contato);
    }

    fclose(arquivo);

    int opcao;
    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Inserir Contato\n");
        printf("2. Buscar Contato\n");
        printf("3. Remover Contato\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            int chave;
            char nome[50], telefone[15], email[50];
            printf("Digite a chave do contato: ");
            scanf("%d", &chave);
            printf("Digite o nome do contato: ");
            scanf("%s", nome);
            printf("Digite o telefone do contato: ");
            scanf("%s", telefone);
            printf("Digite o email do contato: ");
            scanf("%s", email);
            Contato novo_contato;
            strcpy(novo_contato.nome, nome);
            strcpy(novo_contato.telefone, telefone);
            strcpy(novo_contato.email, email);
            inserir(tabela, chave, novo_contato);
            break;
        }
        case 2:
        {
            int chave_busca;
            printf("Digite a chave do contato a ser buscado: ");
            scanf("%d", &chave_busca);
            Contato contato_busca;
            if (buscar(tabela, chave_busca, &contato_busca))
            {
                printf("Contato encontrado: %s - %s - %s\n", contato_busca.nome, contato_busca.telefone, contato_busca.email);
            }
            break;
        }
        case 3:
        {
            int chave_remover;
            printf("Digite a chave do contato a ser removido: ");
            scanf("%d", &chave_remover);
            if (remover(tabela, chave_remover))
            {
                printf("Contato removido com sucesso\n");
            }
            break;
        }
        case 4:
        {
            printf("Saindo do programa\n");
            return 0;
        }
        default:
            printf("Opção inválida\n");
            break;
        }
    }

    return 0;
}
