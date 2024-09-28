#include <stdio.h>
#include <stdlib.h>

#define max(A,B) ((A > B) ? (A) : (B))
#define min(A,B) ((A < B) ? (A) : (B))

struct nodo {
    int chave;
    int h;
    struct nodo* esq;
    struct nodo* dir;
};

typedef struct nodo NODO;

void exibe_preordem (NODO *p) {
    if (p == NULL) {
        printf("arvore nao foi criada\n");
        return;
    }
    printf("ptr_no=%p, chave=%d h=%d esq=%p dir=%p\n", p, p->chave, p->h, p->esq, p->dir);
    if (p->esq != NULL)
        exibe_preordem(p->esq);
    if (p->dir != NULL)
        exibe_preordem(p->dir);
}

int altura(NODO *p) {
    if (p == NULL)
        return -1;
    return p->h;
}

NODO* srotateright(NODO *p) {
    NODO *aux;
    aux = p->esq;
    p->esq = aux->dir;
    aux->dir = p;
    p->h = 1 + max(altura(p->esq), altura(p->dir));
    aux->h = max(altura(aux->esq), p->h) + 1;
    return aux;
}

NODO* srotateleft(NODO *p) {
    NODO *aux;
    aux = p->dir;
    p->dir = aux->esq;
    aux->esq = p;
    p->h = 1 + max(altura(p->esq), altura(p->dir));
    aux->h = max(altura(aux->dir), p->h) + 1;
    return aux;
}

NODO* insertAVL(int x, NODO *p) {
    if (p == NULL) { // cria nó
        p = (NODO*)malloc(sizeof(NODO));
        if (p == NULL)
            return NULL;
        p->chave = x;
        p->esq = p->dir = NULL;
        p->h = 0;
    } else if (x < p->chave) {
        p->esq = insertAVL(x, p->esq);
        if ((altura(p->esq) - altura(p->dir) == 2) ||
            (altura(p->esq) - altura(p->dir) == -2)) {
            if (x < p->esq->chave)
                return srotateright(p);
            p->esq = srotateleft(p->esq);
            return srotateright(p);
        }
        p->h = 1 + max(altura(p->esq), altura(p->dir));
    } else if (x > p->chave) {
        p->dir = insertAVL(x, p->dir);
        if ((altura(p->esq) - altura(p->dir) == 2) ||
            (altura(p->esq) - altura(p->dir) == -2)) {
            if (x > p->dir->chave)
                return srotateleft(p);
            p->dir = srotateright(p->dir);
            return srotateleft(p);
        }
        p->h = 1 + max(altura(p->esq), altura(p->dir));
    } else { // x é igual a p->chave
        printf("chave %d ja existe!!!\n", x);
    }
    return p;
}

int main() {
    int arr[] = {15,17,3,5,2,20,25,13,10,16};
    NODO* raiz = NULL;
    for(int i = 0; i < 10; i++){
        raiz = insertAVL(arr[i], raiz);
    }
    exibe_preordem(raiz);
    return 0;
}
