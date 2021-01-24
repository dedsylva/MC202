#include <stdio.h>
#include <stdlib.h>



typedef struct Grafo {
	int n;
	int **adj;
} Grafo;

typedef struct Grafo * p_grafo;


typedef struct {
	int dist; //distancia ate a fonte
	int v_ant; //vertice anterior
	int ver;
} Item;

typedef struct {
	Item *v; //vetor ordenado de acordo com a distancia ate a fonte
	int n, path; //path é o numero de vertices que compoe o caminho mais rapido
	int *anterior; //mostra o vertice anterior
} FP;

typedef FP * p_fp;

#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)

void troca(int *dist_a, int *dist_b, int *v_ant_a, int *v_ant_b, int *ver_a, int *ver_b){
	int aux_a = *dist_a;
	int aux_b = *v_ant_a; 
	int aux_c = *ver_a;
	*dist_a = *dist_b;
	*v_ant_a = *v_ant_b;
	*ver_a = *ver_b;
	*dist_b = aux_a;
	*v_ant_b = aux_b;
	*ver_b = aux_c;
}


void desce_no_heap(Item *heap, int n, int k){
	int maior_filho;
	if(F_ESQ(k) < n){
		maior_filho = F_ESQ(k);
		if (F_DIR(k) < n && heap[F_ESQ(k)].dist < heap[F_DIR(k)].dist)
			maior_filho = F_DIR(k);
		if (heap[k].dist < heap[maior_filho].dist) {
			troca(&heap[k].dist, &heap[maior_filho].dist, &heap[k].v_ant, &heap[maior_filho].v_ant, &heap[k].ver, &heap[maior_filho].ver);
			desce_no_heap(heap, n, maior_filho);
		}
	}
}

Item extrai_min(p_fp fprio) {
	Item item = fprio->v[0];
	troca(&fprio->v[0].dist, &fprio->v[fprio->n -1].dist, &fprio->v[0].v_ant, &fprio->v[fprio->n -1].v_ant, &fprio->v[0].ver, &fprio->v[fprio->n -1].ver);
	fprio->n --;
	return item;
}


void heapsort(p_fp fprio, int n){
	int k;

	for(k =n/2; k>= 0; k--) //transforma em heap
		desce_no_heap(fprio->v, n, k);
	while (n>1){
		troca(&fprio->v[0].dist, &fprio->v[n-1].dist, &fprio->v[0].v_ant, &fprio->v[n-1].v_ant, &fprio->v[0].ver, &fprio->v[n-1].ver);
		n--;
		desce_no_heap(fprio->v, n, 0);
	}
}


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


p_fp criar_filaprio(int tam){
	p_fp fprio = malloc(sizeof(FP));
	fprio->v = malloc(tam*sizeof(Item));
	fprio->anterior = malloc(tam*sizeof(int));

	return fprio;
}

void insere(p_fp fprio, Item item){
	fprio->v[fprio->n] = item;
	fprio->n++;
}

void inicializa_fprio(p_fp fprio, int tamanho){
	int i;	
	Item novo;


	fprio->n = 0; 
	fprio->path = 0;

	//fonte
	novo.ver = 0;
	novo.dist = 0;
	novo.v_ant = -1; //fonte eh o unico que possui vertice anterior negativo  
	insere(fprio, novo);

	//todos os outros vertices
	novo.dist = 100000; //infinito
	novo.v_ant = -100000; //vertices anteriores indefinidos
	for(i=1; i<tamanho; i++){
		novo.ver = i;
		insere(fprio, novo);
	}
}

//se o vertice ainda esta no heap
int ta_no_heap(p_fp fprio, int i){
	int j;
	for(j=0; j<fprio->n; j++)
		if(fprio->v[j].ver == i)
			return 1;

	return 0;
}


int calcula_distancia(p_fp fprio, int dist_do_min, int peso_do_vizinho){
	return peso_do_vizinho + dist_do_min;
}
//distancia do viz do min ate a fonte = distancia do min ate a fonte (= fprio->v[min].dist)


//adiciona o vertice anterior ao vetor caminho
void adiciona_anterior(Item min, p_fp fprio){
	fprio->anterior[min.ver] = min.v_ant;
}

int calcula_indice(int vertice, p_fp fprio){
	int i;

	//acha o indice
	for(i=0; i< fprio->n; i++)
		if(fprio->v[i].ver == vertice)
			return i;
	return 0;
}

//atualiza a distancia do vertice 
void atualiza(p_fp fprio, int indice, int valor, int min){
	fprio->v[indice].dist = valor;
	fprio->v[indice].v_ant = min; //preenche quem foi o vertice anterior
	return;
}

int comp_do_caminho(p_fp fprio, int fim){
		int comp = 1;
		int loop = 1;
		int i = fim;
	
		while(loop){
			comp++;
			i = fprio->anterior[i];
			if(i == 0)
				break;
		}
		return comp;
}


void caminho(p_fp fprio, int fim, int *menor_caminho, int i){
		
		if(fim ==0){ //caso base
			menor_caminho[fim] = 0;
			//printf("kk %d kk ", i);
			return;
			
			//return fim;
		}
		caminho(fprio, fprio->anterior[fim], menor_caminho, i-1);
		menor_caminho[i] = fim;
		//return;
		//printf("%d ", i);
}

int dijkstra(p_fp fprio, p_grafo g, int fim, int mostrar_caminho){
	inicializa_fprio(fprio, fim+1);
	int aux, indice, min_dist, min = 0;
	min_dist = 0;
	Item min_item;
	int resposta = 0;
	int i, loop = 1;
	while(loop){
		//devolve o menor vertice da lista de prioridade
		min_item = extrai_min(fprio); //retiro do heap a menor dist ate a fonte
		min_dist = min_item.dist;
		min = min_item.ver;

		adiciona_anterior(min_item, fprio); //coloco o vertice anterior

		if (fprio->n == 0 || min_dist == 100000)
			break;

		heapsort(fprio, fprio->n); //ordeno o heap novamente

		//menor distancia dos vizinhos ate a fonte
		//olho para os vizinhos nao visitados (ainda estao no heap)
		for(i=0;i<g->n;i++){
			indice = calcula_indice(i, fprio); //acho qual o indice no heap corresponde o vertice viz->v
			if(g->adj[min][i] > 0 && ta_no_heap(fprio, i) && min_dist != 100000){
					
					aux = calcula_distancia(fprio, min_dist, g->adj[min][i]);

					if (aux < fprio->v[indice].dist){
						atualiza(fprio, indice, aux, min); //atualiza distancia e adiciona o vertice que foi visitado
						
						//se estou falando do vertice que quero
						if(fprio->v[indice].ver == fim)
								resposta = fprio->v[indice].dist;

						heapsort(fprio, fprio->n); //ordena novamente conforme dist ate a fonte
					}
			}
		}
	}

	if(mostrar_caminho)
		fprio->path = comp_do_caminho(fprio, fim);

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

	//cria e imprime a fila de prioridade
	p_fp fprio;
	fprio = criar_filaprio(V);


	int fim = V-1;
	int menor_distancia;
	
	menor_distancia = dijkstra(fprio, g, fim, 1);

	//printf("\n########\n");
	//printf(">> %d << \n", menor_distancia);
	//printf("########\n");
	//printf("\n");

	int *caminho_min = malloc(fprio->path * sizeof(int));
	caminho(fprio, fim, caminho_min, fprio->path -1);
	//for(i=0; i< fprio->path; i++)
		//printf("%d ", caminho_min[i]);

	int comp = 0;
	for(i=0; i<fprio->path; i++){
		comp ++;
		if(caminho_min[i] == fim)
			break;
	}
	fprio->path = comp;


	int viz_fonte = 0;
	int viz_fim = 0;

	viz_fonte = vizinhos_fonte(g); //num de viz da fonte
	viz_fim = vizinhos_fim(g); //num de viz do fim


	int vertice_1, vertice_2; //vertices que formam a aresta que vou eliminar do grafo
	int peso_antigo; //pesos que serao substituidos e depois recolocados
	int seg_menor_dist = 100000; //nossa resposta
	int ares = fprio->path;
	
	
	for(i=0; i<ares -1; i++){
		
		vertice_1 = caminho_min[i];
		vertice_2 = caminho_min[i+1];


		if (viz_fonte || viz_fim)
			continue;


		//retira a aresta do grado, i.e, coloca um peso -1
		peso_antigo = g->adj[vertice_1][vertice_2];
		insere_aresta(g, vertice_1, vertice_2 , -1);
		
		menor_distancia = dijkstra(fprio, g, fim, 0);
		
		//colocamos os pesos de volta
		insere_aresta(g, vertice_1, vertice_2 , peso_antigo);

		if(menor_distancia < seg_menor_dist)
			seg_menor_dist = menor_distancia;

	}

	printf("%d\n", seg_menor_dist);

	return 0;
}
