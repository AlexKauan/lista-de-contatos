# Tabela Hash d=método de Multiplicação e Sondagem Linear 

## Doscente:
   [Kennedy Reurison Lopes](https://github.com/kennedyufersa)

## Discentes:
- [Alex Kauan](https://github.com/AlexKauan)
- [Andrews Ferreira de Paiva Silva](https://github.com/TheFonci)
- [Ângela Maria de Aquino Souza](https://github.com/angellusj)
- [Michely Vitória Costa Felix](https://github.com/MichelyFelix)

## Tabela Hash

Uma tabela hash, também conhecida como tabela de dispersão ou de espalhamento, é uma estrutura de dados utilizada para tornar o processo de busca mais eficiente. A principal ideia por trás de uma tabela hash é converter a chave de pesquisa em um índice de tabela usando funções hash. Essas funções transformam as chaves em valores de índice, permitindo armazenar e acessar informações de forma rápida e eficiente.

Ao converter as chaves em índices, as informações são colocadas na tabela hash tentando evitar o mínimo de colisões, isto é, situações em que chaves diferentes resultam no mesmo índice. No entanto, caso ocorram colisões, existem técnicas para resolvê-las, como sondagem linear, sondagem quadrática, encadeamento ou árvores binárias de busca. Neste contexto, utilizaremos a técnica de sondagem linear para lidar com colisões.

## Metodo de Multiplicação

A chave é umtiplicada por uma constante fracinaria(A), extraimos a perte fracionária da multiplicação e multiplicamos pelo tamanho da tabela e o resultado da multiplicação é armazenado em uma palavra de b bits.

## Sondagem Linear

Quando ocorre uma colisão em uma tabela hash,ou seja duas chaves diferentes resultaram no mesmo índice após a aplicação da função de dispersão. Para lidar com essa situação, empregamos o método de sondagem linear, que consiste em buscar o próximo índice disponível na tabela hash quando um índice já está ocupado.

O processo de sondagem linear pode ser descrito da seguinte maneira:

Após uma colisão ocorrer para uma chave k no índice ℎ(k) da tabela hash, verificamos o próximo índice, h(k)+1, na tabela hash. Se esse próximo índice estiver vazio, inserimos a chave nesse índice.
Se o próximo índice estiver ocupado, continuamos verificando os próximos índices na sequência h(k)+2,h(k)+3, ...) até encontrarmos um índice vazio.
Repetimos esse processo até localizar um índice vazio na tabela hash.
