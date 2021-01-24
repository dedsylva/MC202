# Algoritmo de Yenn


## Objetivo

- O objetivo do programa é calcular o segundo menor caminho de um grafo não direcionado, com um custo W de passar entre dois vértices U e V.


### Entrada

- A primeira linha da entrada é composta por dois inteiros N e M, onde N é a quantidade de vértices do grafo e M a quantidade de arestas;

- Após isso serão dadas M linhas contendo três inteiros: U, V e W, que representa a aresta U, a aresta V e o custo W de passar por elas (tempo para percorrer o caminho, por exemplo).


### Saída

- A saída do programa é composta de um inteiro (com uma quebra de linha) indicando qual a distância do segundo menor caminho do grafo.

### Exemplos

* Entrada

4 5
0 1 1
0 2 3
2 3 4
0 3 1
1 3 2

* Saída

3


### Observações

- Para esse programa, devido ao sistema ser sensível a alocações de memórias, foram feitos dois programas: um utilizando heaps e filas (teoricamente mais rápido) e outro utilizando vetores e matrizes de prioridades (que acabou funcionando na plataforma de deploy do código).