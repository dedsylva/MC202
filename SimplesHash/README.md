# Hash Simples

## Objetivo

- O objetivo desse programa é criar uma implementação de uma tabela de hash, com a seguinte função de hash **h(x) = x%N** , no qual N é o tamanho da tabela. 

- O método de Hash consiste em aplicar a função h(k) e armazenar o elemento na posição resultante. Em caso de colisão (a posição já está preenchida), colocamos na próxima posição. Para esse programa foi implementado um vetor simples.


### Entrada

- A primeira linha da entrada é um número inteiro N < 32767. Esse número representa o tamanho da tabela e quantos elementos serão inseridos.

- A segunda linha é composta por N inteiros representando os elementos a serem inseridos (note que eles podem ser os mesmos).

### Saída

- A saída do programa é um inteiro (com uma quebra de linha) indicando **o número de colisões da tabela hash**.