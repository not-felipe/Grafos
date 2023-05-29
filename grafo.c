#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct lista {
  int destino;
  int custo;
  struct lista *prox;
} lista;

void inicializar (lista **g, int n) {
  int i;
  for(i = 0; i <= n; i++)
    g[i] = NULL;
}

lista *inserirLista (lista *l, int d, int c) {
  lista *no = (lista *) malloc (sizeof(lista));
  no->destino = d;
  no->custo = c;
  no->prox = l;
  return no;
}

void inserirAresta (lista **g, int origem, int destino, int custo) {
  g[origem] = inserirLista(g[origem], destino, custo);
}

void imprimirLista (lista *l) {
  if(l != NULL) {
    printf("-(%d, %d)", l->destino, l->custo);
    imprimirLista(l->prox);
  }
}

void imprimirGrafo (lista **g, int n) {
  int i;
  printf("Grafo: ");
  for(i = 1; i <= n; i++) {
    printf("\n\t%d", i);
    imprimirLista(g[i]);
  }
}

void caminhos (lista **g, int b, int *vet, int pos, int max_size) {
  if (vet[pos-1] == b) {
    int i;
    printf("\n");
    for(i = 0; i < pos; i++) {
      printf("%d ", vet[i]);
    }
  }
  else if (pos < max_size) { // Verifica se o tamanho máximo do vetor não foi excedido
    lista *p = g[vet[pos-1]];
    while(p != NULL) {
      vet[pos] = p->destino;
      caminhos(g, b, vet, pos+1, max_size);
      p = p->prox;
    }
  }
}


int existe (lista *vet, int valor) {
  while(vet != NULL) {
    if(vet->destino == valor)
      return 1;
    vet = vet->prox;
  }
  return 0;
}

int grauEntrada(lista **g, int v, int n) {
  int i, count = 0;
  for(i = 1; i <= n; i++) {
    if (existe(g[i], v))
      count++;
  }
  return count;
}

int grauSaida(lista *l) {
  int count = 0;
  while(l != NULL) {
    count++;
    l = l->prox;
  }
  return count;
}

int verificaCompleto(lista **g, int n) {
  int i, j;
  for(i = 1; i <= n; i++) {
    for(j = 1; j <= n; j++) {
      if(i != j && !existe(g[i], j))
        return 0;
    }
  }
  return 1;
}

void imprimirCaminhoMaisCurto(lista **g, int origem, int destino, int *caminho, int pos) {
  if(origem == destino) {
    caminho[pos] = origem;
    int i;
    for(i = 0; i <= pos; i++)
      printf("%d ", caminho[i]);
    printf("\n");
    return;
  }
  lista *p = g[origem];
  caminho[pos] = origem;
  while(p != NULL) {
    imprimirCaminhoMaisCurto(g, p->destino, destino, caminho, pos + 1);
    p = p->prox;
  }
}

void imprimirCaminhoMenorCusto(lista **g, int origem, int destino, int *caminho, int pos, int custo_atual, int *custo_menor) {
  if(origem == destino) {
    caminho[pos] = origem;
    int i;
    for(i = 0; i <= pos; i++)
      printf("%d ", caminho[i]);
    printf("\n");
    if(custo_atual < *custo_menor)
      *custo_menor = custo_atual;
    return;
  }
  lista *p = g[origem];
  caminho[pos] = origem;
  while(p != NULL) {
    imprimirCaminhoMenorCusto(g, p->destino, destino, caminho, pos + 1, custo_atual + p->custo, custo_menor);
    p = p->prox;
  }
}

int main() {
  int *vet, n;
  int orig, dest, custo;
  lista **g;
  int opt;

  printf("Qual a quantidade de vértices do grafo?\n");
  scanf("%d", &n);

  g = (lista**) malloc((n+1) * sizeof(lista*));
  vet = (int*) malloc(n * sizeof(int));

  inicializar(g, n);

  do {
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
      case 3:
        imprimirGrafo(g, n);
        break;
      case 4:
        printf("Digite o vértice: ");
        scanf("%d", &orig);
        printf("Grau de entrada: %d\n", grauEntrada(g, orig, n));
        printf("Grau de saída: %d\n", grauSaida(g[orig]));
        printf("Grau: %d\n", grauSaida(g[orig]) + grauEntrada(g, orig, n));
        break;
      case 5:
        if(verificaCompleto(g, n))
          printf("O grafo é completo.\n");
        else
          printf("O grafo não é completo.\n");
        break;
      case 6:
        printf("Digite a origem: ");
        scanf("%d", &orig);
        printf("Digite o destino: ");
        scanf("%d", &dest);
    
        caminhos(g, dest, vet, 0, n);
        break;
      case 7:
        printf("Digite a origem: ");
        scanf("%d", &orig);
        printf("Digite o destino: ");
        scanf("%d", &dest);
        int *caminhoMaisCurto = (int*) malloc(n * sizeof(int));
        imprimirCaminhoMaisCurto(g, orig, dest, caminhoMaisCurto, 0);
        free(caminhoMaisCurto);
        break;
      case 8:
        printf("Digite a origem: ");
        scanf("%d", &orig);
        printf("Digite o destino: ");
        scanf("%d", &dest);
        int *caminhoMenorCusto = (int*) malloc(n * sizeof(int));
        int custoMenor = INT_MAX;
        imprimirCaminhoMenorCusto(g, orig, dest, caminhoMenorCusto, 0, 0, &custoMenor);
        printf("Custo mínimo: %d\n", custoMenor);
        free(caminhoMenorCusto);
        break;
      case 9:
        break;
      default:
        printf("Opção inválida.\n");
        break;
    }
  } while(opt != 9);

  free(vet);
  free(g);

  return 0;
}
