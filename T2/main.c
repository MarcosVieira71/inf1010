#include <stdio.h>
#include <stdlib.h>

#define FOLHA 1
#define MAX_CHAVES 3
#define MAX_PONTEIROS 3 

typedef struct No {
    int chaves[MAX_CHAVES];
    struct No* ponteiros[MAX_PONTEIROS];
    int ehFolha;
    int numChaves;
    struct No* pai;
} No;


No* criaNo(int folha, No* pai);
No* cisaoFolha(No* raiz, int valorMeio);
No* insereChave(No* raiz, int chave, int ehFolha);
int encontraIndexInsercaoPonteiro(No* raiz, int chave);
int encontraIndexInsercaoFolha(No* raiz, int chave);
int verificaEhFolha(No* raiz);
void swapNo(No* raiz);

No* criaNo(int folha, No* pai) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return NULL;
    for (int i = 0; i < MAX_CHAVES; i++) novo->chaves[i] = -1;
    for (int i = 0; i < MAX_PONTEIROS; i++) novo->ponteiros[i] = NULL;
    novo->ehFolha = folha;
    novo->numChaves = 0;
    novo->pai = pai;
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

int encontraIndexInsercaoPonteiro(No* raiz, int chave){
    if(raiz->chaves[0] >= chave){
        return 0;
    }
    else if(raiz->chaves[1] <= chave){
        return 1;
    }
    else return 2;
}

int verificaEhFolha(No* raiz){
    for(int i = 0; i < MAX_PONTEIROS; i++){
        if(raiz->ponteiros[i]) return FOLHA;
    }
    return !FOLHA;
}

void swapNo(No* raiz){
    raiz->chaves[0] = raiz->chaves[1]; 
    raiz->chaves[1] = raiz->chaves[2]; 
    raiz->chaves[2] = -1;
    raiz->numChaves--;
}


No* insereChave(No* raiz, int chave, int ehFolha) {
    if (!raiz) {
        raiz = criaNo(ehFolha, NULL);
        if (!raiz) return NULL;
    }

    if(raiz->ehFolha){
        int idxFolha = encontraIndexInsercaoFolha(raiz, chave);
        raiz->chaves[idxFolha] = chave;
        raiz->numChaves++;  
        if(raiz->numChaves== 3){
            return cisaoFolha(raiz, raiz->chaves[1]);
        }
    }
    else{
        int idxPonteiro = encontraIndexInsercaoPonteiro(raiz, chave);
        int ponteiroEhFolha = verificaEhFolha(raiz->ponteiros[idxPonteiro]);
        raiz->ponteiros[idxPonteiro] = insereChave(raiz->ponteiros[idxPonteiro], chave, ponteiroEhFolha);
    }
    return raiz;
}


No* cisaoFolha(No* raiz, int valorMeio){
    if(!(raiz->pai)){
        No* novaRaiz = criaNo(!FOLHA, NULL);
        novaRaiz->chaves[0] = valorMeio;
        
        No** filhoMenor = &(novaRaiz->ponteiros[0]);
        *filhoMenor = insereChave(*(filhoMenor), raiz->chaves[0], FOLHA);
        
        novaRaiz->ponteiros[1] = raiz;
        swapNo(raiz);
        novaRaiz->numChaves++;
        return novaRaiz;
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
    raiz = insereChave(raiz, 15, !FOLHA);
    raiz = insereChave(raiz, 13, !FOLHA);
    raiz = insereChave(raiz, 5, !FOLHA);
    raiz = insereChave(raiz, 20, !FOLHA);
    imprimeArvore(raiz);

    return 0;
}
