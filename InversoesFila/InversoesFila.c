#include <stdio.h>
#include <stdlib.h>


/*
Tadeu Pereira da Silva - 187234 Lab 05 MC 202 1S - 2020
*/


/*
 O objetivo desse lab eh descobrir o numero de inversoes par a par
 	que deve ser realizada para que o vetor esteja ordenado por merge sort
	 (O(n log(n)))
*/

void copia_vetor(unsigned long int *vetor, int N);
unsigned long int merge(unsigned long int *vetor, int l, int m, int r);
unsigned long int mergesort(unsigned long int *v, int l, int r);

void copia_vetor(unsigned long int *vetor, int N){
	int i;
	
	for(i=0;i<N;i++)
		scanf("%lu", &vetor[i]);
	
}

unsigned long int merge(unsigned long int *v, int l, int m, int r){
	unsigned long int *aux = malloc((r+1)*sizeof(unsigned long int));
	unsigned long int cont = 0;
	int i = l, j = m +1, k = 0; 
	//intercala
	while (i <= m && j <= r){
		if (v[i] <= v[j]) //nada a inverter
			aux[k++] = v[i++];
		else{
			aux[k++] = v[j++];
			//se v[i] > v[j] entao todo o bloco da esquerda a partir de i+1 tambem eh maior 
			//logo, como fazemos a inversao digito por digito, havera (m - i + 1) inversoes para cada caso
			// exemplo: 1 9 18 45   |  7 10 23
			// 9 > 7, mas nao vamos trocas as posicoes imediatamente
			// fazemos as inversoes 45 <-> 7, 18 <-> 7 e apenas depois 9 <-> 7

			cont = cont + (m -i + 1);
		}
	}
	//copia o resto do subtevor que nao terminou
	while (i <= m) 
		aux[k++] = v[i++];
	while (j <= r)
		aux[k++] = v[j++];
	
	//copia de volta para vetor
	for(i = l, k = 0; i <= r; i++, k++)
		v[i] = aux[k];
	
	free(aux);
	return cont;

}

unsigned long int mergesort(unsigned long int *v, int l, int r){
	int m = (l +r)/2;
	unsigned long int cont = 0;
	//int troca = 0;
	if (l < r) {
		//divisao
		cont += mergesort(v,l,m);
		cont += mergesort(v, m+1, r);

		//conquista
		cont += merge(v, l, m, r);
	}

	return cont;
}

int main() {
	int N;
	scanf("%d", &N);

	unsigned long int *vetor = malloc(N*sizeof(unsigned long int));
	
	unsigned long int contador = 0; // resposta

	copia_vetor(vetor, N);
	contador = mergesort(vetor, 0, N-1);
	
	printf("%lu\n", contador);


	free(vetor);
	return 0;
}


