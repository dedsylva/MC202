#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
Tadeu Pereira da Silva - 187234 Lab 04 MC 202 1S - 2020
*/

void copiar(char *num, char *novo, int i, int tam);

//copia de um vetor num, ignorando o indice i
void copiar(char *num, char *novo, int i, int tam){
	int j;
	if(i >= 0){
		for (j = 0; j< i; j++){ //copia normal ate o indice que vamos ignorar
		novo[j] = num[j];
		}

		for (j = i+1; j<tam; j++){
			novo[j-1] = num[j];
		}
		novo[tam-1] = '\0'; //mostrando o fim da string


	}

	if (i == -1){ //queremos copiar todo o vetor
		for (j = 0; j< tam; j++){
			novo[j] = num[j];
		}

	}


}


int main () {
	char num[28], num1[28], num2[28], res[28], min[28], menor_num[28];
	int num_zeros = 0; //quantos zeros existem (casos de borda)
	int i, tam, k, j, m;
	int tem_string = 1; //variavel indicadora
	
	//copiamos o num como uma string (vetor de char)
	i = 0;
	while(tem_string) {
		scanf("%c", &num[i]);
		if(num[i] == ' '){ //acabou o num
			num[i] = '\0'; //indicamos que eh uma string
			tem_string = 0;
		}
		else
			i++;
	}

	tam = i;


	scanf("%d", &k); //num de digitos a serem removidos


	//checando para ver se k == num de digitos
	if (tam == k){
		printf("%d", 0);
		return 0;
	}

	//Checando para ver quantos digitos sao zero
	for( i = 0; i < tam; i++){
		if ((num[i]-'0') == 0)
			num_zeros ++;
	}

	if (num_zeros == tam){ //se todos os digitos sao zero
		printf("%d", 0);
		return 0;
	}

	if (num_zeros == (tam-1) && k >= 1){
		printf("%d", 0);
		return 0;
	}




	//algoritmo principal
	/*
	Percorremos o vetor da esquerda para a direita
	Removemos um numero de digito j e outro de j+1
	  - Comparamos qual resulta em um menro num
		- Aquele que for o menor num eh o resultado
		- Repetimos isso para todos os pares possiveis
	Repetimos isso para o num k de digitos que queremos remover
	*/

copiar(num, res, -1, tam);

for(j = 0; j < k; j++){
	//copiar o num sem o i-esimo digito
	for(i = 0; i< tam-1; i++){
		copiar(res, num1, i, tam-j); //ignoro o i-esimo indice
		copiar(res, num2, i+1, tam-j); //copio res para num2 (exceto o i-esimo +1 indice)

		//comparar qual eh o menor num

		for (m = 0; m < (tam-j); m++){
			if ((num1[m]-'0') < (num2[m]-'0')){
				copiar(num1, menor_num, -1, tam-j);
				m = tam-j;
			}
			else{
				copiar(num2, menor_num, -1, tam-j);
				m = tam-j;
			}			
		}

		//inicializacao de valor de min
		if (i==0)
			copiar(menor_num, min, -1, tam-j);

		//garantimos que o min seja global
			for (m = 0; m < (tam-j); m++){
				if((menor_num[m]-'0') < (min[m])-'0'){
					copiar(menor_num, min, -1, tam-j);
					m = tam-j;
				}
				if ((min[m]-'0') < (menor_num[m]-'0'))
					m = tam-j;

			}

		//a resposta final eh o menor numero depois de testar todos os algoritmos
		if (i == (tam-2))
			copiar(min, res, -1, tam-j);

	}
}

	num_zeros = 0;
	//Checando para ver quantos digitos sao zero
	for( i = 0; i < (tam-k); i++){
		if ((res[i]-'0') == 0)
			num_zeros ++;
	}

	if (num_zeros == (tam-k)){ //se todos os digitos sao zero
		printf("%d", 0);
		return 0;
	}



	//checando possiveis zeros a esquerda
for(i=0; i<(tam-k); i++){
		for(m = (tam-k-1); m>=0; m--){
			if (m > 1){
				if (((res[m-1]-'0') + (res[m-2]-'0') == 0) && ((res[m]-'0') != 0) && ((res[m-2]-'0') == 0)) {
					copiar(res, res, m-1, tam-k);
					k ++;

				}
			}
			if (m == 1){
				if (((res[m-1]-'0') == 0) && ((res[m]-'0') != 0)){
					copiar(res, res, m-1, tam-k);
					k ++;
				}
			}
		}
}

	for(m = 0; m< tam-k; m++){
		printf("%c", res[m]);
	}

	return 0;
}