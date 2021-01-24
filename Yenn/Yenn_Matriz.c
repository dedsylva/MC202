#include <stdio.h>
#include <stdlib.h>



typedef struct Grafo {
	int n;
	int **adj;
} Grafo;

typedef struct Grafo * p_grafo;



p_grafo criar_grafo(int n){
	int i, j;
	p_grafo g = malloc(sizeof(Grafo));
	g->n = n;
	g->adj = malloc(n*sizeof(int *));
	
	for(i=0; i<n; i++)
		g->adj[i] = malloc(n*sizeof(int));
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			g->adj[i][j] = 0;
	return g;
}

void insere_aresta(p_grafo g, int u, int v, int peso){
	g->adj[u][v] = peso;
	g->adj[v][u] = peso;
}



//atualiza a distancia do vertice 
void atualiza(int * vertices, int indice, int valor, int min, int *anterior){
	vertices[indice] = valor;
	anterior[indice] = min; //preenche quem foi o vertice anterior
	return;
}

int comp_do_caminho(int *vertices, int *anterior, int fim){
		int comp = 1;
		int loop = 1;
		int i = fim;
	
		while(loop){
			comp++;
			i = anterior[i];
			if(i == 0)
				break;
		}
		return comp;
}

void caminho(int *vertices, int*anterior, int fim, int *menor_caminho, int i){
		
		if(fim ==0){ //caso base
			menor_caminho[fim] = 0;
			//printf("kk %d kk ", i);
			return;
			
			//return fim;
		}
		caminho(vertices, anterior, anterior[fim], menor_caminho, i-1);
		menor_caminho[i] = fim;
		//return;
		//printf("%d ", i);
}


int foi_visitado(int *visitados, int i){
	if(visitados[i] == 1)
		return 1;
	else
		return 0;
}


int calcula_min(int *vertices, int tam, int *visitados){
	int i;
	int min = 100000;
	int indice = 0;
	for(i=0; i<tam; i++){
		if(!foi_visitado(visitados, i) && vertices[i] < min){
			min = vertices[i];
			indice = i;
		}
	}
	return indice;

}

int dijkstra(p_grafo g, int *vertices, int *visitados, int *indices, int* anterior, int fim, int mostrar_caminho, int * path){
	int aux, min = 0;
	int it = 0;
	int resposta = 0;
	int i, loop = 1;

	//iniciando o vetor de vertices com as distancias ate a fonte
	vertices[0] = 0;
	anterior[0] = 0;
	visitados[0] = 0;
	for(i=1; i<fim+1; i++){
		vertices[i] = 100000;
		anterior[i] = -1;
		visitados[i] = 0;
	}

	while(loop){
		//devolve o menor vertice da lista de prioridade
		min = calcula_min(vertices, fim+1, visitados);
		//printf(">>>>>> %d\n", min);

		it ++;


		if (it == fim+1)
			break;

		//menor distancia dos vizinhos ate a fonte
		//olho para os vizinhos nao visitados (ainda estao no heap)
		for(i=0; i<fim+1; i++){
			if(g->adj[min][i] > 0 && !foi_visitado(visitados, i) && vertices[min] != 100000){
					
					//printf("## %d ##\n", i);
					aux = g->adj[min][i] + vertices[min];
					//printf("aux: %d\n", aux);
					//printf("dist. atual de %d: %d\n", i, vertices[i]);

					if(aux < vertices[i]){
						atualiza(vertices, i, aux, min, anterior); //atualiza distancia e adiciona o vertice anterior
						//printf("dist. atualizada de %d: %d\n", i, vertices[i]);


						//se estou falando do vertice que quero
						if(i == fim)
								resposta = vertices[i];
					}

					visitados[min] = 1;
			}
		}
	}

	if(mostrar_caminho)
		* path = comp_do_caminho(vertices, anterior, fim);

	return resposta;
}

//se a fonte possui so um vizinho, nao podemos retirar essa aresta depois
//retorna 1 se ha somente 1 vizinhos, 0 caso contario
int vizinhos_fonte(p_grafo g){
	int i;
	for(i=0; i<g->n;i++)
		if(g->adj[0][i] > 0)
			return 0;
	
	return 1;
}

//analogo para o fim
int vizinhos_fim(p_grafo g){
	int i;
	for(i=0; i<g->n;i++)
		if(g->adj[g->n -1][i] > 0)
			return 0;
	
	return 1;
}

int main(){

	//le e armazena o grafo
	p_grafo g;
	int i,V,A;
	scanf("%d %d", &V, &A);

	g = criar_grafo(V);

	int u,v,peso;
		for(i=0;i<A;i++){
		scanf("%d %d %d", &u, &v, &peso);
		insere_aresta(g, u, v, peso);
	}

	int *vertices;
	vertices = malloc(V*sizeof(int));

	int *visitados;
	visitados = malloc(V*sizeof(int));

	for(i=0; i<V; i++)
		visitados[i] = 0;

	int *indices;
	indices = malloc(V*sizeof(int));

	int *anterior;
	anterior = malloc(V*sizeof(int));

	int comprimento_caminho = 0;
	
	int fim = V-1;
	int menor_distancia;
	
	menor_distancia = dijkstra(g, vertices, visitados, indices, anterior, fim, 1, &comprimento_caminho); 
	//printf("\n########\n");
	//printf(">> %d << \n", menor_distancia);
	//printf("########\n");
	//printf("\n");


	
	int *caminho_min = malloc(comprimento_caminho * sizeof(int));
	caminho(vertices, anterior, fim, caminho_min, comprimento_caminho -1);
	//for(i=0; i< comprimento_caminho; i++)
		//printf("%d ", caminho_min[i]);


	int comp = 0;
	for(i=0; i<comprimento_caminho; i++){
		comp ++;
		if(caminho_min[i] == fim)
			break;
	}
	comprimento_caminho = comp;


	int viz_fonte = 0;
	int viz_fim = 0;

	viz_fonte = vizinhos_fonte(g); //num de viz da fonte
	viz_fim = vizinhos_fim(g); //num de viz do fim


	int vertice_1, vertice_2; //vertices que formam a aresta que vou eliminar do grafo
	int peso_antigo; //pesos que serao substituidos e depois recolocados
	int seg_menor_dist = 100000; //nossa resposta
	int ares = comprimento_caminho;
	

	for(i=0; i<ares -1; i++){
		
		vertice_1 = caminho_min[i];
		vertice_2 = caminho_min[i+1];


		if (viz_fonte || viz_fim)
			continue;


		//retira a aresta do grado, i.e, coloca um peso -1
		peso_antigo = g->adj[vertice_1][vertice_2];
		insere_aresta(g, vertice_1, vertice_2 , -1);
		
		menor_distancia = dijkstra(g, vertices, visitados, indices, anterior, fim, 0, &comprimento_caminho); 


		//colocamos os pesos de volta
		insere_aresta(g, vertice_1, vertice_2 , peso_antigo);

		if(menor_distancia < seg_menor_dist)
			seg_menor_dist = menor_distancia;

	}

	printf("%d\n", seg_menor_dist);

	
	return 0;
}
