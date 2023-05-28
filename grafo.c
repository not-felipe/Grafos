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
  int orig, dest;
  lista **g;

  printf("Qual a quantidade nos do grafo?\n");
  scanf("%d", &n);
  g = (lista **) malloc((n+1)*sizeof(lista*));
  inicializar(g, n);
  vet = (int*) malloc(n*sizeof(int));
  vet[0] = orig;
  caminhos(g, dest, vet, 1);
}