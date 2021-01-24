
/* 
Tadeu Pereira da Silva - 187234 - Lab3 MC202 1S 2020
*/

#include <stdio.h>
#include <stdlib.h>


/*
Definindo a nossa lista ligada
*/

typedef struct No {
int dado;
int cabeca; //variavel indicadora nao utilizada
struct No *prox; //proximo
struct No *ant; //anterior
} No;

typedef struct No * p_no;

/* 
Funçoes utilizadas no programa. 
Algumas foram tiradas dos slides do professor Rafael Schouery
Outras foram modificadas a partir delas
*/

p_no criar_lista_();
p_no inserir_(p_no lista, int x);
p_no remover_(p_no lista, p_no no);
void imprimir_com_seta(p_no lista);
p_no circular(p_no lista, int N, int C);

p_no criar_lista(){
	return NULL;
}

//funcao para inserir: inserimos logo antes da cabeca (no fim da lista)
p_no inserir(p_no lista, int x) {
	p_no novo, ant_da_lista;
	novo = malloc(sizeof(No));
	novo->dado = x;
	if (lista == NULL){
		novo->cabeca = 1;  //cabeca eh a primeira a ser add
		novo->prox = novo; //aponta pra ele mesmo
		novo->ant = novo;
		return novo;
	}
	else { //adiciono sempre no final 
	
		for(ant_da_lista = lista->prox; ant_da_lista->prox != lista; ant_da_lista = ant_da_lista->prox); //acho o anterior da lista
		novo->cabeca = 0;
		novo->prox = lista; //o elemento adicionado aponta para a cabeca
		novo->ant = lista->ant;
		lista->ant = novo;
		
		ant_da_lista->prox = novo;
	
		return lista;
	}	
}

//funcao remover: removemos o no, encontrando o seu anterior, ajeitamos os ponteiros de ant e prox, e liberamos o no da lista
p_no remover(p_no lista, p_no no) {

	// se a lista ta vazia
	if(lista == NULL)
		return NULL;

	//se so ha um elemento eu deixo novamente a lista vazia
	if(lista->prox == lista){
		free(no);
		return NULL;
	}

	p_no ant_do_no;

	for(ant_do_no = no->prox; ant_do_no->prox != no; ant_do_no = ant_do_no->prox);
	ant_do_no->prox = no->prox;
	no->prox->ant = ant_do_no;
		
		//se quero remover a cabeca nao posso devolver ela, mas tenho que devolver a nova cabeca
	if(no == lista){
		free(no);
		return ant_do_no->prox;
	}

	free(no);
	return lista;		


}

p_no circular(p_no lista, int N, int C){
	int i, posicao; // i-esima posicao da lista, contando a partir da cabeca
	for (i=0; i< N; i++){
		posicao = (C+i) % N;
		lista = inserir(lista, posicao);
	}
	return lista;
}


//Funcao principal: atendimento dos dois clientes, um pela direita (com k espacos) e outro pela esquerda (com l espacos)
// percorremos k vezes pela direita e l vezes para a esquerda
// verifico se o cliente atendido nao e igual
// 	--> se nao for, imprimo cada cliente e os removo da lista
//  --> se os clientes forem os mesmos, imprimo-os e os removo da lista (apenas uma vez)
// reinicializo a contagem (esquerda = 0; direita = 0)
// faco esse loop ate que a lista seja vazia (condicao de que todos os clientes foram atendidos)

void atender(p_no lista, int N, int C, int k, int l){
	//atendente 1 anda k-posicoes para a direita
	int direita = 0;
	//atendente 2 anda k-posicoes para a esquerda
	int esquerda = 0;
	
	p_no atende_dir, atende_esq; //ponteiro pra percorrer a lista
	atende_dir = lista;
	atende_esq = lista;
	
	//percorro enquanto ha 1 elemento
	while( lista != NULL){
	  //percorre a lista ate achar o cliente da direita	
		while(direita != k){
			atende_dir = atende_dir->prox;
			direita ++;
		}
		//percorre a lista ate achar o cliente da esquerda
		


		
		while(esquerda != l){
			atende_esq = atende_esq->ant;
			esquerda ++;
		}

		// se os atendentes nao atendem o mesmo cliente
		if(atende_dir->dado != atende_esq->dado){
			printf("%d ", atende_dir->dado);
			printf("%d\n", atende_esq->dado);
			lista = remover(lista, atende_esq);
			lista = remover(lista, atende_dir);

		}		
		else{
			printf("%d ", atende_dir->dado);
			printf("%d\n", atende_esq->dado);
			lista = remover(lista, atende_esq);

		}
		esquerda = 0;
		direita = 0;

		if(atende_esq->ant == atende_dir)
			esquerda --;



	}
}

int main() {

	p_no lista;
	lista = criar_lista();
	
	int N, C, k, l;
	scanf("%d %d %d %d", &N, &C, &k, &l);

	//Criamos a lista circular duplamente conectada
	lista = circular(lista, N, C);

	atender(lista, N, C, k, l);

	return 0;

}