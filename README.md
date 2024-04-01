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
A tabela hash foi implementada utilizando uma estrutura de dados de dispersão que mapeia chaves para valores. O tamanho da tabela (TABLE_SIZE) foi definido como 50, para manter um equilíbrio entre eficiência de espaço e tempo de acesso, considerando-se o número de contatos esperados. Essas escolhas visam otimizar o desempenho da tabela hash, garantindo um bom tempo de acesso e minimizando colisões, enquanto mantêm a implementação simples e eficiente.

Durante a implementação do código, alguns problemas foram identificados, porém solucionados em seguida, sendo eles:

- Problema de colisão: Onde duas chaves diferentes resultaram no mesmo índice de tabela hash. Como solução, foi implementada a técnica de sondagem linear, reduzindo a probabilidade de colisões e mantendo a eficiência da tabela.

- Capacidade da tabela: Se a tabela hash estivesse cheia, não conseguiríamos inserir novos elementos. Para solucionar esse problema, implementou-se uma verificação durante a inserção para saber se a tabela está cheia.

- Remoção de Elementos: Houve dificuldades para remover um elemento da tabela sem corromper a estrutura de dados. A solução encontrada para esse problema foi implementar uma marcação para os elementos removidos, permitindo que a busca funcione corretamente, evitando falsos positivos.
  
- *Implementação do Método da Multiplicação*: Multiplicamoa a chave por uma constante e depois extraimos a parte fracinária.
```c
  int hash(int chave) {
    // Método de multiplicação
    return (int)((chave * 0.6180339887) * TABLE_SIZE) % TABLE_SIZE;
}
```

- *Implementação da Sondagem Linear*: Quando ocorre uma colisão, uma nova posição é buscada incrementando até encontrar uma posição que esteja vazia.
```c
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

```
