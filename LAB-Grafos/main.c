#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertice;
    int distancia;
    struct Node* prox;
} Node;

typedef struct Graph {
    int v; 
    Node** adj;  
} Graph;

typedef struct Edge {
    int inicial;
    int final;
    int distancia;
} Edge;

Node* criarNo(int vertice) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->vertice = vertice;
    novoNo->prox = NULL;
    return novoNo;
}

Graph* criarGrafo(int v){
    Graph* grafo = (Graph*)malloc(sizeof(Graph));
    grafo->v = v;
    grafo->adj = (Node**)malloc(v * sizeof(Node*));
    for (int i = 0; i < v; i++) {
        grafo->adj[i] = NULL;
    }
    return grafo;
}

void adicionarAresta(Graph* grafo, Edge aresta) {
    Node* novoNo = criarNo(aresta.final);
    novoNo->prox = grafo->adj[aresta.inicial];
    novoNo->distancia = aresta.distancia;
    grafo->adj[aresta.inicial] = novoNo;

    novoNo = criarNo(aresta.inicial);
    novoNo->distancia = aresta.distancia;
    novoNo->prox = grafo->adj[aresta.final];
    grafo->adj[aresta.final] = novoNo;
}

void imprimirGrafo(Graph* grafo) {
    for (int i = 0; i < grafo->v; i++) {
        Node* temp = grafo->adj[i];
        if (temp) {
            printf("Vértice %d: ", i);
            while (temp != NULL) {
                printf("%d (Distância: %d)", temp->vertice, temp->distancia);
                temp = temp->prox;
                if (temp) printf(" -> ");
            }
            printf("\n");
        }
    }
}

void imprimirGrafoComoMatriz(Graph* grafo) {
    int matriz[grafo->v][grafo->v];
    for (int i = 0; i < grafo->v; i++) {
        for (int j = 0; j < grafo->v; j++) {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < grafo->v; i++) {
        Node* temp = grafo->adj[i];
        while (temp != NULL) {
            matriz[i][temp->vertice] = temp->distancia;
            temp = temp->prox;
        }
    }

    printf("\nMatriz de Adjacências:\n\n");
    for (int i = 0; i < grafo->v; i++) {
        for (int j = 0; j < grafo->v; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void buscaPorAmplitude(Graph* grafo, int inicio) {
    if (inicio < 0 || inicio >= grafo->v) {
        printf("Índice de início fora dos limites\n");
        return;
    }

    int* visitados = (int*)malloc(grafo->v * sizeof(int));
    if (!visitados) {
        printf("Erro ao alocar memória para visitados\n");
        return;
    }
    for (int i = 0; i < grafo->v; i++) {
        visitados[i] = 0;
    }

    int* fila = (int*)malloc(grafo->v * sizeof(int));
    if (!fila) {
        printf("Erro ao alocar memória para fila\n");
        free(visitados);
        return;
    }

    int inicioFila = 0, fimFila = 0;

    visitados[inicio] = 1;
    fila[fimFila++] = inicio;

    while (inicioFila < fimFila) {
        int verticeAtual = fila[inicioFila++];
        printf("Visitando vértice %d\n", verticeAtual);

        Node* adjacente = grafo->adj[verticeAtual];
        while (adjacente != NULL) {
            int vizinho = adjacente->vertice;
            if (!visitados[vizinho]) {
                visitados[vizinho] = 1;
                fila[fimFila++] = vizinho;
            }
            adjacente = adjacente->prox;
        }
    }

    free(fila);
    free(visitados);
}

int compararArestas(const void* a, const void* b) {
    Edge* arestaA = (Edge*)a;
    Edge* arestaB = (Edge*)b;
    return arestaA->distancia - arestaB->distancia;
}


int find(int x, int* parent) {
    if (parent[x] != x)
        parent[x] = find(parent[x], parent);
    return parent[x];
}

void setUnion(int x, int y, int* parent) {
        int raizX = find(x, parent);
        int raizY = find(y, parent);
        parent[raizX] = raizY;
    }


void kruskal(Edge* arestas, int totalArestas, int numVertices) {
    qsort(arestas, totalArestas, sizeof(Edge), compararArestas);

    

    int* parent = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        parent[i] = i; 
    }

    printf("\nArestas da Árvore Geradora Mínima:\n\n");
    for (int i = 0; i < totalArestas; i++) {
        int u = arestas[i].inicial;
        int v = arestas[i].final;

        if (find(u, parent) != find(v, parent)) { 
            printf("(%d, %d) com peso %d\n", u, v, arestas[i].distancia);
            setUnion(u, v, parent);
        }
    }

    free(parent);
}



int main() {
    Graph* grafo = criarGrafo(10);

    Edge arestas[] = {
        {0, 1, 4}, {0, 8, 8}, {1, 8, 11}, {1, 3, 8}, {8, 9, 7},
        {8, 7, 1}, {9, 3, 2}, {9, 7, 6}, {7, 6, 2}, {3, 6, 4},
        {3, 4, 7}, {4, 6, 14}, {4, 5, 9}, {6, 5, 10}
    };

    int numArestas = sizeof(arestas) / sizeof(arestas[0]);
    for (int i = 0; i < numArestas; i++) {
        adicionarAresta(grafo, arestas[i]);
    }

    imprimirGrafo(grafo);
    imprimirGrafoComoMatriz(grafo);

    printf("\nBusca em Amplitude:\n\n");

    buscaPorAmplitude(grafo, 0);

    kruskal(arestas, numArestas, grafo->v);

    return 0;
}