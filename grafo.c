#include <stdio.h>
#include <stdlib.h>

typedef struct Adjacente {
    int destino;
    int custo;
    struct Adjacente* prox;
} Adjacente;

typedef struct {
    Adjacente** vertices;
    int numVertices;
} Grafo;

void inicializarGrafo(Grafo* grafo, int numVertices) {
    grafo->numVertices = numVertices;
    grafo->vertices = (Adjacente**)malloc(numVertices * sizeof(Adjacente*));
    for (int i = 0; i < numVertices; i++) {
        grafo->vertices[i] = NULL;
    }
}

void inserirAresta(Grafo* grafo, int origem, int destino, int custo) {
    if (origem >= 0 && origem < grafo->numVertices && destino >= 0 && destino < grafo->numVertices) {
        Adjacente* novoAdjacente = (Adjacente*)malloc(sizeof(Adjacente));
        novoAdjacente->destino = destino;
        novoAdjacente->custo = custo;
        novoAdjacente->prox = grafo->vertices[origem];
        grafo->vertices[origem] = novoAdjacente;
    } else {
        printf("Vértices inválidos.\n");
    }
}

void removerAresta(Grafo* grafo, int origem, int destino) {
    if (origem >= 0 && origem < grafo->numVertices && destino >= 0 && destino < grafo->numVertices) {
        Adjacente* atual = grafo->vertices[origem];
        Adjacente* anterior = NULL;

        while (atual != NULL) {
            if (atual->destino == destino) {
                if (anterior == NULL) {
                    grafo->vertices[origem] = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                free(atual);
                break;
            }
            anterior = atual;
            atual = atual->prox;
        }
    } else {
        printf("Vértices inválidos.\n");
    }
}

void imprimirGrafo(Grafo* grafo) {
    printf("Grafo:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("Vértice %d:", i);
        Adjacente* atual = grafo->vertices[i];
        while (atual != NULL) {
            printf(" -> %d (Custo: %d)", atual->destino, atual->custo);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void imprimirGrausVertice(Grafo* grafo, int vertice) {
    int grauEntrada = 0, grauSaida = 0;
    if (vertice >= 0 && vertice < grafo->numVertices) {
        for (int i = 0; i < grafo->numVertices; i++) {
            Adjacente* atual = grafo->vertices[i];
            while (atual != NULL) {
                if (atual->destino == vertice) {
                    grauEntrada++;
                }
                if (i == vertice) {
                    grauSaida++;
                }
                atual = atual->prox;
            }
        }
        printf("Grau de entrada do vértice %d: %d\n", vertice, grauEntrada);
        printf("Grau de saída do vértice %d: %d\n", vertice, grauSaida);
    } else {
        printf("Vértice inválido.\n");
    }
}

int verificarGrafoCompleto(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        int numAdjacentes = 0;
        Adjacente* atual = grafo->vertices[i];
        while (atual != NULL) {
            numAdjacentes++;
            atual = atual->prox;
        }
        if (numAdjacentes != grafo->numVertices - 1) {
            return 0;
        }
    }
    return 1;
}

void imprimirCaminhos(Grafo* grafo, int origem, int destino, int* caminho, int tamanho) {
    caminho[tamanho] = origem;

    if (origem == destino) {
        printf("Caminho encontrado: ");
        for (int i = 0; i <= tamanho; i++) {
            printf("%d ", caminho[i]);
        }
        printf("\n");
    } else {
        Adjacente* atual = grafo->vertices[origem];
        while (atual != NULL) {
            imprimirCaminhos(grafo, atual->destino, destino, caminho, tamanho + 1);
            atual = atual->prox;
        }
    }
}

void imprimirCaminhoMaisCurto(Grafo* grafo, int origem, int destino) {
    int* caminho = (int*)malloc(grafo->numVertices * sizeof(int));
    printf("Caminho mais curto:\n");
    imprimirCaminhos(grafo, origem, destino, caminho, 0);
    free(caminho);
}

void imprimirCaminhoMenorCusto(Grafo* grafo, int origem, int destino, int* caminho, int tamanho, int custoAtual, int* menorCusto, int* caminhoMenorCusto) {
    caminho[tamanho] = origem;
    if (origem == destino) {
        if (custoAtual < *menorCusto) {
            *menorCusto = custoAtual;
            for (int i = 0; i <= tamanho; i++) {
                caminhoMenorCusto[i] = caminho[i];
            }
        }
    } else {
        Adjacente* atual = grafo->vertices[origem];
        while (atual != NULL) {
            imprimirCaminhoMenorCusto(grafo, atual->destino, destino, caminho, tamanho + 1, custoAtual + atual->custo, menorCusto, caminhoMenorCusto);
            atual = atual->prox;
        }
    }
}

void imprimirCaminhoDeMenorCusto(Grafo* grafo, int origem, int destino) {
    int* caminho = (int*)malloc(grafo->numVertices * sizeof(int));
    int* caminhoMenorCusto = (int*)malloc(grafo->numVertices * sizeof(int));
    int menorCusto = grafo->numVertices + 1;
    imprimirCaminhoMenorCusto(grafo, origem, destino, caminho, 0, 0, &menorCusto, caminhoMenorCusto);
    printf("Caminho de menor custo: ");
    for (int i = 0; i < menorCusto; i++) {
        printf("%d ", caminhoMenorCusto[i]);
    }
    printf("\n");
    free(caminho);
    free(caminhoMenorCusto);
}

void liberarGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        Adjacente* atual = grafo->vertices[i];
        while (atual != NULL) {
            Adjacente* proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }
    free(grafo->vertices);
}

int main() {
    int numVertices;
    printf("Digite o número de vértices do grafo: ");
    scanf("%d", &numVertices);

    Grafo grafo;
    inicializarGrafo(&grafo, numVertices);

    int opcao;
    int origem, destino, custo;

    while (1) {
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
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a origem da aresta: ");
                scanf("%d", &origem);
                printf("Digite o destino da aresta: ");
                scanf("%d", &destino);
                printf("Digite o custo da aresta: ");
                scanf("%d", &custo);
                inserirAresta(&grafo, origem, destino, custo);
                break;
            case 2:
                printf("Digite a origem da aresta a ser removida: ");
                scanf("%d", &origem);
                printf("Digite o destino da aresta a ser removida: ");
                scanf("%d", &destino);
                removerAresta(&grafo, origem, destino);
                break;
            case 3:
                imprimirGrafo(&grafo);
                break;
            case 4:
                printf("Digite o vértice: ");
                scanf("%d", &origem);
                imprimirGrausVertice(&grafo, origem);
                break;
            case 5:
                if (verificarGrafoCompleto(&grafo)) {
                    printf("O grafo é completo.\n");
                } else {
                    printf("O grafo não é completo.\n");
                }
                break;
            case 6:
                printf("Digite a origem do caminho: ");
                scanf("%d", &origem);
                printf("Digite o destino do caminho: ");
                scanf("%d", &destino);
                int* caminho = (int*)malloc(numVertices * sizeof(int));
                imprimirCaminhos(&grafo, origem, destino, caminho, 0);
                free(caminho);
                break;
            case 7:
                printf("Digite a origem do caminho: ");
                scanf("%d", &origem);
                printf("Digite o destino do caminho: ");
                scanf("%d", &destino);
                imprimirCaminhoMaisCurto(&grafo, origem, destino);
                break;
            case 8:
                printf("Digite a origem do caminho: ");
                scanf("%d", &origem);
                printf("Digite o destino do caminho: ");
                scanf("%d", &destino);
                imprimirCaminhoDeMenorCusto(&grafo, origem, destino);
                break;
            case 9:
                liberarGrafo(&grafo);
                exit(0);
            default:
                printf("Opção inválida.\n");
                break;
        }
    }

    return 0;
}
