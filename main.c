#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 50
#define LOAD_FACTOR_MIN 25
#define LOAD_FACTOR_MAX 75
//Variáveis globais para definir o tamanho da tabela com a capacidade total de 25 a 75 (Sem Colisão) de todos os contatos.

typedef struct {
    char nome[50];
    char telefone[15];
    char email[50]
} Contato;
//Estrutura dos contatos para armazenar os contatos que serão lidos do arquivo.

typedef struct {
    int chave;
    Contato contato;
    int ocupado;
    int removido;
} EntradaTabelaHash;
// Estrutura que representa uma entrada na tabela hash, contendo a chave, o contato, e indicadores de se a posição está ocupada (ocupado) ou se o contato foi removido (removido).

void inicializarTabela(EntradaTabelaHash tabela[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela[i].ocupado = 0;
        tabela[i].removido = 0;
    }
}
//Função que inicializa todas as entradas da tabela como não ocupadas e não removidas.

int hash(int chave) {
    // Método de multiplicação
    return (int)((chave * 0.6180339887) * TABLE_SIZE) % TABLE_SIZE;
}
//Função que calcula o índice da tabela hash para uma determinada chave usando o método de multiplicação.

void inserir(EntradaTabelaHash tabela[], int chave, Contato contato) {
    int posicao = hash(chave);
    int inicial = posicao;
    int inserido = 0;

    do {
        if (!tabela[posicao].ocupado || tabela[posicao].removido) {
            tabela[posicao].chave = chave;
            tabela[posicao].contato = contato;
            tabela[posicao].ocupado = 1;
            tabela[posicao].removido = 0;
            inserido = 1;
            printf("Contato inserido com sucesso na posição %d\n", posicao);
        } else {
            posicao = (posicao + 1) % TABLE_SIZE;
        }
    } while (!inserido && posicao != inicial);

    if (!inserido) {
        printf("Não foi possível inserir o contato. Tabela cheia.\n");
    }
}
/* Função que insere um contato na tabela hash.
Calcula o índice usando a função hash.
Tenta inserir na posição calculada, se a posição estiver ocupada, tenta a próxima posição (sondagem linear) até encontrar uma posição livre.
Se não encontrar uma posição livre, a inserção falha.*/

int buscar(EntradaTabelaHash tabela[], int chave, Contato *contato) {
    int posicao = hash(chave);
    int inicial = posicao;

    do {
        if (tabela[posicao].ocupado && !tabela[posicao].removido && tabela[posicao].chave == chave) {
            *contato = tabela[posicao].contato;
            printf("Contato encontrado na posição %d\n", posicao);
            return 1; // Encontrou o contato
        } else if (!tabela[posicao].ocupado) {
            printf("Contato não encontrado\n");
            return 0; // Contato não encontrado
        } else {
            posicao = (posicao + 1) % TABLE_SIZE;
        }
    } while (posicao != inicial);

    printf("Contato não encontrado\n");
    return 0; // Contato não encontrado
}
/*Função que busca um contato na tabela hash.
Calcula o índice usando a função hash.
Procura na posição calculada e nas próximas posições (sondagem linear) até encontrar o contato ou uma posição livre.
Se encontrar o contato, retorna o contato encontrado, caso contrário, retorna que o contato não foi encontrado.*/

int main() {

  FILE *f = fopen("todosOsContatos.txt", "r");
  char *nome;
  char *tel;
  char *email;

  nome = (char *)malloc(20 * sizeof(char));
  tel = (char *)malloc(20 * sizeof(char));
  email = (char *)malloc(20 * sizeof(char));

  for (int i = 0; i < 10000; i++) {

    fscanf(f, "Nome: %[A-Z. a-z]\n", nome);
    fscanf(f, "Telefone: %[(0-9) -0-9]\n", tel);
    fscanf(f, "Email: %s\n", email);
    fscanf(f, "\n");

    printf("%d\n", i);
    printf("%s\n", nome);
    printf("%s\n", tel);
    printf("%s\n", email);

  }
}