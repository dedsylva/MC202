# Alocação Dinâmica

## Objetivos: 

* Adicionar X casos de corona vírus para pacientes com idade Y;

* Responder quantos casos de corona vírus existem em pacientes com a idade em [X,Y].

- Dado um vetor alocado dinamicamente podemos consultar quantos casos tem e adicionar novos nesse vetor.

### Restrições

* Vetor inicializado com 5 posições;

* Alocar o dobro de posições sempre que precisar.

### Entrada

- Entrada é composta por um inteiro P indicando quantas operações o usuário quer fazer, depois P linhas com 1 ou 0. 

- Caso 0 -> Adicionar caso;
- Caso 1 -> Consultar;


### Saída

* 1 inteiro + quebra de linha se input for Consultar.

### Exemplos

* 0 5 12

Nesse exemplo queremos Adicionar 5 pacientes com idade de 12 anos

* 1 18 30

Nesse exemplo queremos Consultar quantos casos existem com pacientes entre 18 e 30 anos.

