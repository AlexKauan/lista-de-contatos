# Tabela Hash método de Multiplicação e Sondagem Linear 

## Docente:
   [Kennedy Reurison Lopes](https://github.com/kennedyufersa)

## Discentes:
- [Alex Kauan de Oliveira Lima](https://github.com/AlexKauan)
- [Andrews Ferreira de Paiva Silva](https://github.com/TheFonci)
- [Ângela Maria de Aquino Souza](https://github.com/angellusj)
- [Michely Vitória Costa Félix](https://github.com/MichelyFelix)

## Introdução

Programa escrito em linguagem C que armazena uma lista telefônica  extraida de [todosOsContatos](https://github.com/AlexKauan/lista-de-contatos/blob/main/todosOsContatos.txt) em uma tabela Hash/disperção. Este programa utiliza o metodo de multiplicação para implementar a tabela de disperção e para tratar as colições é utilazado a sondagem linear.

## Principais Operações

- Inserção
- Busca
- Remoção
  
### Interface Gráfica
A interface gráfica escolhida para estre projeto foi por meio de arquivos, o resultado da hash pode ser visto pelo arquivo  ou pelo gdb.
### Configuração da Tablea Hash
A tabela hash foi implementada utilizando uma estrutura de dados de dispersão que mapeia chaves para valores. O tamanho da tabela (TABLE_SIZE) foi definido como 40000, para manter um equilíbrio entre eficiência de espaço e tempo de acesso, considerando-se o número de contatos esperados. Essas escolhas visam otimizar o desempenho da tabela hash, garantindo um bom tempo de acesso e minimizando colisões, enquanto mantêm a implementação simples e eficiente.

Durante a implementação do código, alguns problemas foram identificados, porém solucionados em seguida, sendo eles:

- Problema de colisão: Onde duas chaves diferentes resultaram no mesmo índice de tabela hash. Como solução, foi implementada a técnica de sondagem linear, reduzindo a probabilidade de colisões e mantendo a eficiência da tabela.

- Capacidade da tabela: Se a tabela hash estivesse cheia, não conseguiríamos inserir novos elementos. Para solucionar esse problema, implementou-se uma verificação durante a inserção para saber se a tabela está cheia.

- Remoção de Elementos: Houve dificuldades para remover um elemento da tabela sem corromper a estrutura de dados. A solução encontrada para esse problema foi implementar uma marcação para os elementos removidos, permitindo que a busca funcione corretamente, evitando falsos positivos.
  
- *Implementação do Método da Multiplicação*: Multiplicamoa a chave por uma constante e depois extraimos a parte fracinária.
```c
 double hash(int chave)
{
    return (chave * 0.2) / TABLE_SIZE;
}
```

- *Implementação da Sondagem Linear*: Quando ocorre uma colisão, uma nova posição é buscada incrementando até encontrar uma posição que esteja vazia.
```c
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

```
