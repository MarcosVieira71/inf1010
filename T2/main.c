#include <stdio.h>
#include <stdlib.h>

#define FOLHA 1
#define MAX_CHAVES 2
#define MAX_PONTEIROS 3 

typedef struct No {
    int chaves[MAX_CHAVES];
    struct No* ponteiros[MAX_PONTEIROS];
    int ehFolha;
    int numChaves;
} No;

No* criaNo(int folha) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return NULL;
    for (int i = 0; i < MAX_CHAVES; i++) novo->chaves[i] = -1;
    for (int i = 0; i < MAX_PONTEIROS; i++) novo->ponteiros[i] = NULL;
    novo->ehFolha = folha;
    novo->numChaves = 0;
    return novo;
}

// Encontra posição para inserir ordenadamente
int encontraIndexInsercaoFolha(No* raiz, int chave){
    int i = raiz->numChaves - 1;
    while (i >= 0 && raiz->chaves[i] > chave) {
        raiz->chaves[i + 1] = raiz->chaves[i]; // Desloca a chave maior
        i--;
    }
    return i + 1;
}



int verificaEhFolha(No* raiz){
    for(int i = 0; i < MAX_PONTEIROS; i++){
        if(raiz->ponteiros[i]) return FOLHA;
    }
    return !FOLHA;
}

No* insereChave(No* raiz, int chave, int ehFolha) {
    if (!raiz) {
        raiz = criaNo(ehFolha);
        if (!raiz) return NULL;
    }


    if(!raiz->ehFolha){
        if(chave < raiz->chaves[0]){
            raiz->ponteiros[0] = insereChave(raiz->ponteiros[0], chave, FOLHA);
        }
    }
    if(raiz->numChaves < MAX_CHAVES){
        int index = encontraIndexInsercaoFolha(raiz, chave);
        raiz->chaves[index] = chave;
        raiz->numChaves++;
    }
    else{
        if(chave < raiz->chaves[0]){
            No* novaRaiz = NULL;
            novaRaiz = insereChave(novaRaiz, raiz->chaves[0], !FOLHA);
            novaRaiz->ponteiros[0] = insereChave(raiz->ponteiros[0], chave, FOLHA);
            novaRaiz->ponteiros[1] = raiz;
            return novaRaiz;
        }
    }
    return raiz;
}




void imprimeArvore(No* no) {
    if (no == NULL) return;
    printf("No: %p, chaves: [", no);
    for (int i = 0; i < no->numChaves; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->numChaves - 1) printf(", ");
    }
    printf("], ptrs: [");
    for (int i = 0; i <= no->numChaves; i++) {
        if (no->ponteiros[i] != NULL)
            printf("%p", no->ponteiros[i]);
        else
            printf("NULL");
        if (i < no->numChaves) printf(", ");
    }
    printf("]\n");

    for (int i = 0; i <= no->numChaves; i++) {
        if (no->ponteiros[i] != NULL)
            imprimeArvore(no->ponteiros[i]);
    }
}

int main() {
    No* raiz = NULL;
    raiz = insereChave(raiz, 10,FOLHA);
    raiz = insereChave(raiz, 5, !FOLHA); 
    raiz = insereChave(raiz, 1, !FOLHA);
    raiz = insereChave(raiz, 2, !FOLHA);
    imprimeArvore(raiz);

    return 0;
}
