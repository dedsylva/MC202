// 0 -> Adicionar X casos para pacientes com Y anos
// 1 -> Consultar quantos casos existem no intervalo [X,Y]

/* 
Tadeu Pereira da Silva - 187234 - Lab2 MC202 1S 2020
*/

#include <stdio.h>
#include <stdlib.h>

void Adicionar(int x, int y, int *dados, int tam, int adicionados);
int Consultar(int x, int y, int *dados, int tam, int adicionados);

void Adicionar(int x, int y, int *dados, int tam, int adicionados){
	//Adicionamos o vetor dado por [num idade]
	if (adicionados == 0){ //se estamos adicionando o primeiro elemento
		dados[0] = x;
		dados[1] = y;
	}
	else {
		dados[adicionados*2] = x;
		dados[adicionados*2 +1] = y;
	}				
	
	
}

int Consultar(int x, int y, int *dados, int tam, int adicionados){
	int valor = 0;
	int i, j;
	int posicoes = (adicionados*2 + 1); //num de posicoes que foram ocupadas pelo vetor
	
	for(i = x; i <= y; i++){
		for (j = 1; j < posicoes; j = j + 2){ //Achamos a idade certa no vetor (lembrando que como ele nao esta ordenado, precisamos percorrer ele todo)
			if (dados[j] == i) { //Encontramos a entrada que representa a idade desejada. 
				//printf("%d", dados[j]);
				valor = valor + dados[j-1]; //Pegamos o num de casos correspondente a idade desejada (lembrando o vetor é da forma [num idade])
			}
		}
	}

	return valor;
}

int main(){
	int *dados = malloc(5 * sizeof(int));
	int i, n, x, y, consulta;
	int adicionados = 0; 
	int tam = 5; //tamanho inicial

	scanf("%d", &n);
	
	for(i = 0; i < n; i++){
		scanf("%d %d %d", &consulta, &x, &y);

		//Verificamos se temos o tamanho necessario
		if (adicionados*2 >= tam){
			tam = 2* tam;
			dados = realloc(dados, tam * sizeof(int));
		}
		
		if(consulta == 1){ //se a funcao escolhida eh consultar
			printf("%d\n", Consultar(x, y, dados, tam, adicionados));
		}
		else{
			Adicionar(x, y, dados, tam, adicionados); //Adiciona x e y no vetor dados de tamanho m 
			adicionados ++; //quantas posicoes ja foram adicionadas
		}
	}

	free(dados);

	return 0;
}