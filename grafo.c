#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct lista {
  int destino;
  int custo;
  struct lista* prox;
} lista;

void inicializar(lista** grafo, int n) {
  for (int i = 0; i <= n; i++) {
    grafo[i] = NULL;
  }
}

void inserirAresta(lista** grafo, int origem, int destino, int custo) {
  lista* novoNo = (lista*)malloc(sizeof(lista));
  novoNo->destino = destino;
  novoNo->custo = custo;
  novoNo->prox = grafo[origem];
  grafo[origem] = novoNo;
}

void removerAresta(lista** grafo, int origem, int destino) {
  lista* atual = grafo[origem];
  lista* anterior = NULL;

  while (atual != NULL) {
    if (atual->destino == destino) {
      if (anterior == NULL) {
        grafo[origem] = atual->prox;
      } else {
        anterior->prox = atual->prox;
      }
      free(atual);
      return;
    }
    anterior = atual;
    atual = atual->prox;
  }
}

void imprimirGrafo(lista** grafo, int n) {
  for (int i = 1; i <= n; i++) {
    printf("Vértice %d:", i);
    lista* atual = grafo[i];
    while (atual != NULL) {
      printf(" -> (%d, %d)", atual->destino, atual->custo);
      atual = atual->prox;
    }
    printf("\n");
  }
}

int grauEntrada(lista** grafo, int vertice, int n) {
  int grau = 0;
  for (int i = 1; i <= n; i++) {
    lista* atual = grafo[i];
    while (atual != NULL) {
      if (atual->destino == vertice) {
        grau++;
      }
      atual = atual->prox;
    }
  }
  return grau;
}

int grauSaida(lista* listaAdj) {
  int grau = 0;
  lista* atual = listaAdj;
  while (atual != NULL) {
    grau++;
    atual = atual->prox;
  }
  return grau;
}

int verificaCompleto(lista** grafo, int n) {
  for (int i = 1; i <= n; i++) {
    if (grauSaida(grafo[i]) != n - 1) {
      return 0;
    }
  }
  return 1;
}

void caminhos(lista** grafo, int origem, int destino, int* visitados, int pos, int* caminho) {
  visitados[origem] = 1;
  caminho[pos++] = origem;

  if (origem == destino) {
    printf("%d", caminho[0]);
    for (int i = 1; i < pos; i++) {
      printf(" -> %d", caminho[i]);
    }
    printf("\n");
  } else {
    lista* atual = grafo[origem];
    while (atual != NULL) {
      if (!visitados[atual->destino]) {
        caminhos(grafo, atual->destino, destino, visitados, pos, caminho);
      }
      atual = atual->prox;
    }
  }

  visitados[origem] = 0;
}

void imprimirCaminhoMaisCurto(lista** grafo, int origem, int destino, int* visitados, int* distancias, int n) {
  for (int i = 1; i <= n; i++) {
    visitados[i] = 0;
    distancias[i] = INT_MAX;
  }

  visitados[origem] = 1;
  distancias[origem] = 0;

  int fila[n];
  int inicio = 0, fim = 0;
  fila[fim++] = origem;

  while (inicio != fim) {
    int vertice = fila[inicio++];
    lista* atual = grafo[vertice];
    while (atual != NULL) {
      if (!visitados[atual->destino]) {
        fila[fim++] = atual->destino;
        visitados[atual->destino] = 1;
        distancias[atual->destino] = distancias[vertice] + 1;
      }
      atual = atual->prox;
    }
  }

  if (distancias[destino] == INT_MAX) {
    printf("Não existe caminho entre %d e %d.\n", origem, destino);
  } else {
    printf("Caminho mais curto: %d", origem);
    int vertice = origem;
    while (vertice != destino) {
      lista* atual = grafo[vertice];
      int proximo = -1;
      while (atual != NULL) {
        if (distancias[atual->destino] == distancias[vertice] + 1) {
          proximo = atual->destino;
          break;
        }
        atual = atual->prox;
      }
      if (proximo != -1) {
        printf(" -> %d", proximo);
        vertice = proximo;
      } else {
        break;
      }
    }
    printf("\n");
  }
}

int custoAresta(lista **g, int a, int b){
  lista *p = g[a];
  while(p != NULL){
    if(p->destino == b)
      return p->custo;
    p = p->prox;
  }
  return -1;
}

int calculaCusto(lista **g, int *vet, int n){
  int i, custo = 0;
  for(i=1; i<n; i++)
    custo += custoAresta(g, vet[i-1], vet[i]);
  return custo;
}

int existe(int *vet, int valor, int n){
  int i;
  for(i = 0; i < n; i++)
    if(vet[i] == valor)
      return 1;
  return 0;
}

void menorCusto (lista **g, int destino, int *vetor, int posicao, int *atual, int custo,int *minimo,int *tamanho) {
  if (vetor[posicao-1] == destino) 
  {
    if (*minimo > custo) 
    {
      *tamanho = posicao;
      *minimo = custo;
      for (int i = 0; i < posicao; i++) 
      {
        atual[i] = vetor[i];
      }
    }
      
  } 
  else 
  {
    custo = 0;
    lista *p = g[vetor[posicao-1]];
    while (p != NULL) 
    {
      if (!existe(vetor,p->destino,posicao)) 
      {
        vetor[posicao] = p->destino;
        custo = custo + p->custo;
        menorCusto(g, destino, vetor, posicao+1, atual, custo, minimo, tamanho);
      }
      p = p->prox;
    }
  }
}

void imprimirMenorCusto (lista **g,int destino, int *vetor, int posicao, int *atual, int custo, int *minimo, int *tamanho) 
{
  menorCusto(g, destino, vetor, posicao, atual, custo, minimo, tamanho);
  for (int i = 0; i < *tamanho; i++) 
  {
    printf("%d ", atual[i]);
  }
}


int main() {
  int *vet, n;
  int orig, dest, custo;
  lista** g;
  int opt;
  int *menorCusto = (int*)900;

  printf("Qual a quantidade de vértices do grafo?\n");
  scanf("%d", &n);

  g = (lista**)malloc((n + 1) * sizeof(lista*));
  vet = (int*)malloc(n * sizeof(int));

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
      case 2:
        printf("Digite a origem da aresta: ");
        scanf("%d", &orig);
        printf("Digite o destino da aresta: ");
        scanf("%d", &dest);
        removerAresta(g, orig, dest);
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
        if (verificaCompleto(g, n))
          printf("O grafo é completo.\n");
        else
          printf("O grafo não é completo.\n");
        break;
      case 6:
        printf("Digite a origem: ");
        scanf("%d", &orig);
        printf("Digite o destino: ");
        scanf("%d", &dest);
        printf("Caminhos possíveis:\n");
        caminhos(g, orig, dest, vet, 0, vet);
        break;
      case 7:
        printf("Digite a origem: ");
        scanf("%d", &orig);
        printf("Digite o destino: ");
        scanf("%d", &dest);
        int* distancias = (int*)malloc((n + 1) * sizeof(int));
        imprimirCaminhoMaisCurto(g, orig, dest, vet, distancias, n);
        free(distancias);
        break;
      case 8:
        {
          int *atual;
          int minimo = 1000000;
          int tam;
          atual = (int*) malloc(n *sizeof(int));
        printf("Digite a origem: ");
        scanf("%d", &orig);
        printf("Digite o destino: ");
        scanf("%d", &dest);
        vet[0] = orig;
        imprimirMenorCusto(g, dest, vet, 1, atual, custo, &minimo, &tam);
        break;
        }
      case 9:
        printf("Encerrando o programa.\n");
        break;
      default:
        printf("Opção inválida.\n");
        break;
    }
  } while (opt != 9);

  free(vet);
  for (int i = 0; i <= n; i++) {
    lista* atual = g[i];
    while (atual != NULL) {
      lista* prox = atual->prox;
      free(atual);
      atual = prox;
    }
  }
  free(g);

  return 0;
}
