#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHAVES 2
#define MIN_CHAVES 1

typedef struct no No;
struct no
{
    int qtdChaves;
    int qtdFilhos;
    int chaves[MAX_CHAVES + 1];
    struct no* ponteirosFilhos[MAX_CHAVES + 2];
    bool ehFolha;
};

No* criarNo(bool ehFolha) 
{
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->qtdChaves = 0;
    novoNo->qtdFilhos = 0;
    novoNo->ehFolha = ehFolha;

    // Inicializa as chaves e ponteiros
    for (int i = 0; i < MAX_CHAVES + 1; i++) novoNo->chaves[i] = -1;
    for (int i = 0; i < MAX_CHAVES + 2; i++) novoNo->ponteirosFilhos[i] = NULL;

    return novoNo;
}

void dividirRaiz(No* raiz) 
{
    No* filhoEsq = criarNo(raiz->ehFolha);
    No* filhoDir = criarNo(raiz->ehFolha);

    filhoEsq->qtdChaves = MIN_CHAVES;
    if (raiz->ehFolha) filhoDir->qtdChaves = MAX_CHAVES;
    else filhoDir->qtdChaves = MIN_CHAVES;
    

    if (raiz->ehFolha) 
    {
        for (int i = 0; i < raiz->qtdChaves; i++)
        {
            filhoDir->chaves[i] = raiz->chaves[i + 1];
        }
    } 
    else filhoDir->chaves[0] = raiz->chaves[2];

    filhoEsq->chaves[0] = raiz->chaves[0];
    raiz->chaves[0] = raiz->chaves[1];
    raiz->chaves[1] = -1;
    raiz->qtdChaves = 1;

    if (!raiz->ehFolha) 
    {
        for (int i = 0; i < 2; i++) 
        {
            filhoEsq->ponteirosFilhos[i] = raiz->ponteirosFilhos[i];
            filhoDir->ponteirosFilhos[i] = raiz->ponteirosFilhos[i + 2];
        }
        filhoEsq->qtdFilhos = filhoDir->qtdFilhos = 2;
    }

    raiz->ponteirosFilhos[0] = filhoEsq;
    raiz->ponteirosFilhos[1] = filhoDir;
    raiz->qtdFilhos = 2;
    raiz->ehFolha = false;
}

void dividirFilho(No* pai, int idx) 
{
    No* filho = pai->ponteirosFilhos[idx];
    No* novoFilho = criarNo(filho->ehFolha);

    if (filho->ehFolha)novoFilho->qtdChaves = MAX_CHAVES;
    else novoFilho->qtdChaves = MIN_CHAVES;

    if (filho->ehFolha) 
    {
        for (int i = 0; i < filho->qtdChaves; i++) 
        {
            novoFilho->chaves[i] = filho->chaves[i + 1];
        }
    } 
    
    else novoFilho->chaves[0] = filho->chaves[2];

    int i = pai->qtdChaves;
    while (i > 0 && pai->chaves[i - 1] > filho->chaves[1]) 
    {
        pai->chaves[i] = pai->chaves[i - 1];
        pai->ponteirosFilhos[i + 1] = pai->ponteirosFilhos[i];
        i--;
    }

    pai->chaves[i] = filho->chaves[1];
    pai->ponteirosFilhos[idx + 1] = novoFilho;
    pai->qtdChaves++;
    pai->qtdFilhos++;

    filho->qtdChaves = MIN_CHAVES;
    filho->chaves[1] = filho->chaves[2] = -1;

    if (!filho->ehFolha) 
    {
        novoFilho->ponteirosFilhos[0] = filho->ponteirosFilhos[2];
        novoFilho->ponteirosFilhos[1] = filho->ponteirosFilhos[3];
        filho->ponteirosFilhos[2] = NULL;
        filho->ponteirosFilhos[3] = NULL;
        novoFilho->qtdFilhos = 2;
        filho->qtdFilhos = 2;
    }
}

void inserirChave(No* no, int chave) 
{
    int i = no->qtdChaves;

    if (no->ehFolha) 
    {
        while (i > 0 && no->chaves[i - 1] > chave) 
        {
            no->chaves[i] = no->chaves[i - 1];
            i--;
        }
        no->chaves[i] = chave;
        no->qtdChaves++;
    } 
    else 
    {
        while (i > 0 && no->chaves[i - 1] > chave) i--;
        inserirChave(no->ponteirosFilhos[i], chave);

        if (no->ponteirosFilhos[i]->qtdChaves > MAX_CHAVES) dividirFilho(no, i);
    }
}

No* inserir(No* raiz, int chave) 
{
    if (!raiz) 
    {
        raiz = criarNo(true);
        raiz->chaves[0] = chave;
        raiz->qtdChaves++;
        return raiz;
    }

    inserirChave(raiz, chave);

    if (raiz->qtdChaves > MAX_CHAVES) dividirRaiz(raiz);

    return raiz;
}

No* buscar(No* raiz, int chave) 
{
    if (raiz == NULL) return NULL;

    int i = 0;
    while (i < raiz->qtdChaves && chave > raiz->chaves[i])i++;

    if (i < raiz->qtdChaves && chave == raiz->chaves[i]) return raiz;
    if (raiz->ehFolha) return NULL;

    return buscar(raiz->ponteirosFilhos[i], chave);
}


void imprimirArvore(No* no) 
{
    if (!no) return;

    printf("%p, chaves do no - (", no);

    for (int i = 0; i < no->qtdChaves; i++) 
    {
        printf("%d", no->chaves[i]);
        if (i < no->qtdChaves - 1) printf(", ");
    }

    printf(") - Ponteiros {");
    
    for (int i = 0; i <= no->qtdChaves; i++) 
    {
        if (no->ponteirosFilhos[i]) printf("%p", no->ponteirosFilhos[i]);
        else printf("NULL");
        if (i < no->qtdChaves) printf(", ");
    }
    printf("}\n");

    for (int i = 0; i <= no->qtdChaves; i++) imprimirArvore(no->ponteirosFilhos[i]);
}

int main() {
    No* raiz = NULL;
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 11);
    raiz = inserir(raiz, 12);

    printf("Árvore antes da exclusão:\n");
    imprimirArvore(raiz);

    printf("\nBuscando a chave 6 na árvore:\n");
    No* resultado = buscar(raiz, 6);
    printf("Chave 6 encontrada no nó com o endereço: %p\n", (void*)resultado);

    return 0;
}
