/*
Tadeu Pereira da Silva - 187234 Lab 07 MC 202 1S - 2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct No {
	int dado;
	int h; 
	struct No *esq, *dir, *pai;
} No;
typedef No * p_no;

p_no inserir(p_no raiz, int dado, int h);


/*
O programa tem como objetivo calcular a altura de 
duas árvores binárias, com o mesmo número de elementos N.

O algoritmo funciona da seguinte forma:
- Para cada novo valor inserido na árvore, calculamos qual
a altura que ele percorreu.
- Comparamos se a altura nova é maior do que havia antes
na árvore.
- Fazendo isso recursivamente chegamos no valor da maior
altura, correspondente a altura da árvore inteira.
- Colocamos esse resultado na raiz, com a variável
int h (atualizada para cada novo elemento inserido)

*/



//retorna o ponteiro da raiz
p_no inserir(p_no raiz, int dado, int h){
	p_no novo;
	if(raiz == NULL) {
		novo = malloc(sizeof(No));
		novo->esq = novo->dir = NULL;
		novo->dado = dado;
		novo->h = h;
		return novo;
	}
	h ++;
	if (dado < raiz->dado){//insiro na esquerda
		raiz->esq = inserir(raiz->esq, dado, h);
		//atualizo a nova altura do elemento inserido
		raiz->h = raiz->esq->h;
	}
	else{ //insiro na direita
		raiz->dir = inserir(raiz->dir, dado, h);
		//atualizo a nova altura do elemento inserido
		raiz->h = raiz->dir->h;
	}
	
	return raiz;
}



int main() {
	int N, i;
	scanf("%d", &N);

	int altura1, altura2,valor;
	altura1 = altura2 = valor = 0;
	
	p_no raiz = malloc(sizeof(No));
	raiz = NULL;

	//primeira arvore
	for(i=0; i< N; i++){
		scanf("%d", &valor);
		raiz = inserir(raiz, valor, 1);
		
		//atualizo a maior altura da arvore
		if (raiz->h > altura1)
			altura1 = raiz->h;
	}

	raiz = NULL;
	
	//segunda arvore
	for(i=0; i< N; i++){
		scanf("%d", &valor);
		raiz = inserir(raiz, valor, 1);
		
		//atualizo a maior altura da arvore
		if (raiz->h > altura2)
			altura2 = raiz->h;			
	}

	printf("%d %d\n", altura1, altura2);

	return 0;
}