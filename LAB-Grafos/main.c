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
    return grafo;
}

void adicionarAresta(Graph* grafo, int inicial, int final, int distancia) {
    Node* novoNo = criarNo(final);
    novoNo->prox = grafo->adj[inicial];
    novoNo->distancia = distancia;
    grafo->adj[inicial] = novoNo;

    novoNo = criarNo(inicial);
    novoNo->distancia = distancia;
    novoNo->prox = grafo->adj[final];
    grafo->adj[final] = novoNo;
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

    printf("Matriz de Adjacências:\n");
    for (int i = 0; i < grafo->v; i++) {
        for (int j = 0; j < grafo->v; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
}


int main() {
    Graph* grafo = criarGrafo(9);

    adicionarAresta(grafo, 0, 1, 4);
    adicionarAresta(grafo, 0, 8, 8);
    adicionarAresta(grafo, 1, 8, 11);
    adicionarAresta(grafo, 1, 3, 8);
    adicionarAresta(grafo, 8, 9, 7);
    adicionarAresta(grafo, 8, 7, 1);
    adicionarAresta(grafo, 9, 3, 2);
    adicionarAresta(grafo, 9, 7, 6);
    adicionarAresta(grafo, 7, 6, 2);
    adicionarAresta(grafo, 3, 6, 4);
    adicionarAresta(grafo, 3, 4, 7);
    adicionarAresta(grafo, 4, 6, 14);
    adicionarAresta(grafo, 4, 5, 9);
    adicionarAresta(grafo, 6, 5, 10);


    imprimirGrafo(grafo);
    imprimirGrafoComoMatriz(grafo);

    return 0;
}