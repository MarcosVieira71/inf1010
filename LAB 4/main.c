#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node
{
    Node *pai;
    int chave;
    int numSub;
    int altura;
    Node *dir;
    Node *esq;
};

Node *insereNo(Node *raiz, int chave);
Node *criaNo(int chave);
void exibeArvore(Node *raiz);
int verificaAbb(Node *raiz);
int contaSubNos(Node *raiz);
int verificaAbb(Node *raiz);
void preencheVetor(Node *raiz, int *arr, int *index);
void liberaArvore(Node *raiz);
int atualizaAltura(Node *raiz);
int verificaAVL(Node *raiz);

int main(void)
{
    int arr[] = {15, 17, 3, 5, 2, 20, 25, 13, 10, 16};
    Node *raiz = NULL;
    for (int i = 0; i < 10; i++)
    {
        raiz = insereNo(raiz, arr[i]);
    }
    atualizaAltura(raiz);
    printf("\nExibicao antes da contagem de sub-nos\n");
    exibeArvore(raiz);
    contaSubNos(raiz);
    printf("\nExibicao apos a contagem de sub-nos\n");
    exibeArvore(raiz);
    if (verificaAbb(raiz))
        printf("\nABB!\n");
    if (verificaAVL(raiz))
        printf("AVL\n");
    liberaArvore(raiz);
}

void exibeArvore(Node *raiz)
{
    if (!raiz)
        return;
    exibeArvore(raiz->esq);
    printf("Raiz %p - Chave %d - NumSubs %d - Filho Dir %p - Filho Esq %p - Altura %d\n", raiz, raiz->chave, raiz->numSub, raiz->dir, raiz->esq, raiz->altura);
    exibeArvore(raiz->dir);
}

Node *insereNo(Node *raiz, int chave)
{
    if (raiz == NULL)
    {
        return criaNo(chave);
    }
    if (raiz->chave > chave)
    {
        raiz->esq = insereNo(raiz->esq, chave);
    }

    else if (raiz->chave < chave)
    {
        raiz->dir = insereNo(raiz->dir, chave);
    }
    return raiz;
}

Node *criaNo(int chave)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        exit(1);
    newNode->chave = chave;
    newNode->pai = NULL;
    newNode->dir = NULL;
    newNode->esq = NULL;
    newNode->numSub = 0;
    newNode->altura = 0;
    return newNode;
}

int verificaAbb(Node *raiz)
{
    if (!raiz)
        return 0;
    int numNos = contaSubNos(raiz);

    int *arr = (int *)malloc(sizeof(int) * numNos);

    int index = 0;

    preencheVetor(raiz, arr, &index);
    for (int i = 0; i < numNos - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            free(arr);
            return 0;
        }
    }
    free(arr);
    return 1;
}

int contaSubNos(Node *raiz)
{
    if (!raiz)
        return 0;
    int qtdEsq = contaSubNos(raiz->esq);
    int qtdDir = contaSubNos(raiz->dir);
    raiz->numSub = qtdEsq + qtdDir;
    return raiz->numSub + 1;
}

void preencheVetor(Node *raiz, int *arr, int *index)
{
    if (raiz == NULL)
        return;

    preencheVetor(raiz->esq, arr, index);

    arr[*index] = raiz->chave;
    (*index)++;

    preencheVetor(raiz->dir, arr, index);
}

void liberaArvore(Node *raiz)
{
    if (!raiz)
        return;
    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);
    free(raiz);
}

int atualizaAltura(Node *raiz)
{
    if (!raiz)
        return -1;
    int alturaesq = atualizaAltura(raiz->esq);
    int alturadir = atualizaAltura(raiz->dir);
    raiz->altura = ((alturaesq > alturadir) ? alturaesq : alturadir) + 1;

    return raiz->altura;
}

int verificaAVL(Node *raiz)
{
    if (!raiz)
        return 1;

    if (!verificaAbb(raiz))
        return 0;

    int alturaesq = raiz->esq ? raiz->esq->altura : -1;
    int alturadir = raiz->dir ? raiz->dir->altura : -1;

    if (abs(alturaesq - alturadir) > 1)
        return 0;

    return verificaAVL(raiz->esq) && verificaAVL(raiz->dir);
}