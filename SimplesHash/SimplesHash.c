/* 
Tadeu Pereira da Silva - 187234 - Lab10 MC202 1S 2020
*/

#include <stdio.h>
#include <stdlib.h>

//zera todas as posicoes do vetor (tabela)
void criar_tabela(int *V, int N){
	int i;
	for(i=0;i<N;i++){
		V[i] = 0;
	}
}

int hash(int *V, int N, int x){
	int i, posicao, colisoes;
	posicao = x %N;

	//se der colocamos na posicao desejada
	if(V[posicao] == 0){
		V[posicao] = x;
		return 0;
	}
	else{ //caso contrario percorremos a tabela ate o fim
		for(i=posicao;i<N;i++){
			if(V[i] == 0){
				V[i] = x;
				return colisoes;
			}
			else
				colisoes ++;
		}
		//percorremos a tabela desde o inicio ate encontrar a posicao
		for(i=0; i<posicao; i++){
			if(V[i] == 0){
				V[i] = x;
				return colisoes;
			}
			else
				colisoes ++;
		}
		return colisoes;
	}
}

int main() {

	int i, N, x, colisoes;;
	int *V;

	scanf("%d" ,&N); 
	V = malloc(N*sizeof(int));
	criar_tabela(V, N);

	colisoes = 0;
	for(i=0;i<N;i++){
		scanf("%d", &x);
		colisoes = colisoes + hash(V, N, x);
	}
	
	printf("%d\n", colisoes);

	return 0;
}