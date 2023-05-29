#include<stdio.h>
#include<stdlib.h>

typedef struct lista {
  int destino;
  int custo;
  struct lista *prox;
} lista;

void inicializar (lista **g, int n){
  int i;
  for(i = 0; i <= n; i+1) //<= pois com um grafo de 4 nós, teremos de inicializar de 1 a 4, posição 0 nao é utilizada
    g[i] = NULL;
}

lista *inserirLista (lista *l, int d, int c){
  lista *no = (lista *) malloc (sizeof(lista));
  no->destino = d;
  no->custo = c;
  no-> prox = l;
  return no;
}

void inserirAresta (lista **g, int origem, int destino, int custo) {
  g[origem] = inserirLista(g[origem], destino, custo);
}

void imprimirLista(lista *l){
  if(l != NULL){
    printf("-(%d, %d)", l->destino, l->custo);
    imprimirLista(l->prox);
  }
}

void imprimirGrafo (lista **g, int n){
  int i;
  printf("Grafo: ");
  for(int i = 1; i <= n; i++){
    printf("\n\t%d", i);
    imprimirLista(g[i]);
  }
}

void caminhos (lista **g, int b, int *vet, int pos){
  if (vet[pos-1] == b){
    int i;
    printf("\n");
    for(i = 0; i < pos; i++){
      printf("%d", vet[i]);
    }
  }
  else{
    lista *p = g[vet[pos-1]];
    while(p!= NULL){
      vet[pos] = p->destino;
      caminhos(g, b, vet, pos+1);
      p = p->prox;
    }
  }
}

int existe (int *vet, int valor, int n){
  int i;
  for(i = 0; i < n; i++)
    if(vet[i] == valor) return 1;
  return 0;
}

int main(){

  int *vet, n;
  int orig, dest, custo;
  lista **g, *l;

  int opt;

  printf("Qual a quantidade de vertices do grafo?\n");
  scanf("%d", &n);

  g = (lista**) malloc((n+1)*sizeof(lista*));


  do{
        printf("\n1: Inserir uma aresta no grafo\n");
        printf("2: Remover uma aresta do grafo\n");
        printf("3: Imprimir grafo\n");
        printf("4: Imprimir os graus de entrada e saída de um vértice\n");
        printf("5: Verificar se um grafo é completo\n");
        printf("6: Imprimir todos os caminhos entre uma origem e um destino\n");
        printf("7: Imprimir o caminho mais curto (com menor número de arestas)\n");
        printf("8: Imprimir o caminho de menor custo (menor soma dos custos das arestas)\n");
        printf("9: Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                printf("Digite a origem da aresta: ");
                scanf("%d", &orig);
                printf("Digite o destino da aresta: ");
                scanf("%d", &dest);
                printf("Digite o custo da aresta: ");
                scanf("%d", &custo);
                inserirAresta(g, orig, dest, custo);
                break;
            // case 2:
            //     printf("Digite a origem da aresta a ser removida: ");
            //     scanf("%d", &orig);
            //     printf("Digite o destino da aresta a ser removida: ");
            //     scanf("%d", &dest);
            //     removerAresta(g, orig, dest);
            //     break;
            case 3:
                imprimirGrafo(g, n);
                break;
            // case 4:
            //     printf("Digite o vértice: ");
            //     scanf("%d", &orig);
            //     imprimirGrausVertice(g, orig);
            //     break;
            // case 5:
            //     if (verificarGrafoCompleto(g)) {
            //         printf("O grafo é completo.\n");
            //     } else {
            //         printf("O grafo não é completo.\n");
            //     }
            //     break;
            // case 6:
            //     printf("Digite a origem do caminho: ");
            //     scanf("%d", &orig);
            //     printf("Digite o destino do caminho: ");
            //     scanf("%d", &dest);
            //     int* caminho = (int*)malloc(n * sizeof(int));
            //     imprimirCaminhos(g, orig, dest, caminho, 0);
            //     free(caminho);
            //     break;
            // case 7:
            //     printf("Digite a origem do caminho: ");
            //     scanf("%d", orig);
            //     printf("Digite o destino do caminho: ");
            //     scanf("%d", dest);
            //     imprimirCaminhoMaisCurto(g, orig, dest);
            //     break;
            // case 8:
            //     printf("Digite a origem do caminho: ");
            //     scanf("%d", &orig);
            //     printf("Digite o destino do caminho: ");
            //     scanf("%d", &dest);
            //     imprimirCaminhoDeMenorCusto(g, orig, dest);
            //     break;
            // case 9:
            //     liberarGrafo(g);
            //     exit(0);
            default:
                printf("Opção inválida.\n");
                break;
        }
  }while( opt!= 9 );

  return 0;
}