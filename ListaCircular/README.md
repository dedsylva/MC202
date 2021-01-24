# Lista Circular

## Introdução

- Temos um sistema com 2 funcionários que atendem N clientes simultaneamente. Cada cliente ganha uma senha distinta indo de 0 até N-1, formando um círculo de ordem crescente de suas senhas. Após isso é escolhido um cliente **arbitrário** C para formar a cabeça da lista circular, sendo a segunda posição da lista (C+1) mod N e a última posição (C-1+N) mod N (ou seja, sentido horário a partir de C).

- Com a lista montada o primeiro atendente chama o cliente que está **a k posições à direita de C** e depois o que tiver k posições do atendido, e assim por diante. O segundo atendente chama o cliente que está **a l posições à esquerda de C** e depois o que tiver l posições do atendido, e assim por diante. Suponha que depois de ser atendido o cliente vai embora e todo cliente demora o mesmo tempo para ser atendido.

- Note que os dois atendentes podem ter que atender o mesmo cliente ao mesmo tempo. Se isso ocorrer, um tira folga e o outro acaba o atendimento.


### Restrições

* Armazenar os dados em lista duplamente encadeada;

* Cada vez que um cliente for atendido, deletar o elemento da lista.

### Entrada

- A entrada é composta pro 4 inteiros: N, C, k e l, indicando respectivamente: quantidade de clientes, o cliente que será a cabeça da lista (primeiro cliente da lista), critérios de escolha para o primeiro e segundo atendente.


### Saída

- A saída contém X linhas com dois inteiros Y e Z, onde a i-ésima linha contém quantos clientes foram atendidos pelo primeiro e pelo segundo atendente.
