# Tabela Hash método de Multiplicação e Sondagem Linear 

## Doscente:
   [Kennedy Reurison Lopes](https://github.com/kennedyufersa)

## Discentes:
- [Alex Kauan de Oliveira Lima](https://github.com/AlexKauan)
- [Andrews Ferreira de Paiva Silva](https://github.com/TheFonci)
- [Ângela Maria de Aquino Souza](https://github.com/angellusj)
- [Michely Vitória Costa Félix](https://github.com/MichelyFelix)

## Introdução

Programa escrito em linguagem C que armazena uma lista telefônica  extraida de [todosOsContatos](https://github.com/AlexKauan/lista-de-contatos/blob/main/todosOsContatos.txt) em uma tabela Hash/disperção. Este programa utiliza o metodo de multiplicação para implementar a tabela de disperção e para tratar as colições é utilazado a sondagem linear.
### Metodo de Multiplicação

A chave é umtiplicada por uma constante fracinária(A), extraimos a perte fracionária da multiplicação e multiplicamos pelo tamanho da tabela e o resultado da multiplicação é armazenado em uma palavra de b bits.

### Sondagem Linear

Quando ocorre uma colisão em uma tabela hash,ou seja duas chaves diferentes resultaram no mesmo índice após a aplicação da função de dispersão. Para lidar com essa situação, empregamos o método de sondagem linear, que consiste em buscar o próximo índice disponível na tabela hash quando um índice já está ocupado.

O processo de sondagem linear pode ser descrito da seguinte maneira:

Após uma colisão ocorrer para uma chave k no índice ℎ(k) da tabela hash, verificamos o próximo índice, h(k)+1, na tabela hash. Se esse próximo índice estiver vazio, inserimos a chave nesse índice.
Se o próximo índice estiver ocupado, continuamos verificando os próximos índices na sequência h(k)+2,h(k)+3, ...) até encontrarmos um índice vazio.
Repetimos esse processo até localizar um índice vazio na tabela hash.
