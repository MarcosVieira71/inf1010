#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

typedef struct arvore Arvore;
struct arvore
{
	Arvore *pai;
	int chave;
	int nivel;
	int altura;
	Arvore *dir;
	Arvore *esq;
};

Arvore *criaArvore(Arvore* pai, int chave);
void insereArvoreNivel(Arvore **raiz, int chave);
void exibeArvore(Arvore *raiz);
void liberaArvore(Arvore* raiz);
void atualizaAltura(Arvore *raiz);

int main(void)
{
	int arr[] = {10, 5, 15, 3, 7, 13, 20, 1, 4, 6};
	Arvore *raiz = NULL;
	for (int i = 0; i < 10; i++)
	{
		insereArvoreNivel(&raiz, arr[i]);
	}
	printf("\nExibindo arvore em pre ordem:\n");
	exibeArvore(raiz);
	liberaArvore(raiz);
}

void insereArvoreNivel(Arvore **raiz, int chave)
{
	if (*raiz == NULL)
	{
		*raiz = criaArvore(NULL, chave);
		return;
	}
	else
	{
		// Aloca memória para a fila que será usada na busca por nível
		Arvore **fila = (Arvore **)malloc(sizeof(Arvore *) * 10);
		int inicio = 0, final = 0;
		fila[final] = *raiz;
		final++;
		while (inicio < final)
		{
			Arvore *arvAtual = fila[inicio];
			inicio++;
			// Se o filho esquerdo está vazio, insere o novo nó aqui
			if (!arvAtual->esq)
			{
				arvAtual->esq = criaArvore(arvAtual, chave);
                atualizaAltura(arvAtual->esq); // Atualiza as alturas
				break;
			}
			else
			{
				fila[final] = arvAtual->esq; // Adiciona o filho esquerdo à fila
				final++;
			}
			// Se o filho direito está vazio, insere o novo nó aqui
			if (!arvAtual->dir)
			{
				arvAtual->dir = criaArvore(arvAtual, chave);
                atualizaAltura(arvAtual->dir); // Atualiza as alturas
				break;
			}
			else
			{
				fila[final] = arvAtual->dir; // Adiciona o filho direito à fila
				final++;
			}
		}
		free(fila);
	}
}

Arvore *criaArvore(Arvore* pai, int chave)
{
	Arvore *a = (Arvore *)malloc(sizeof(Arvore));
	if (a == NULL)
		return NULL;
	a->chave = chave;
	a->dir = NULL;
	a->esq = NULL;
	a->pai = pai;
	a->nivel = (a->pai ? a->pai->nivel+1: 0);
	a->altura = 0;
	return a;
}

void exibeArvore(Arvore *raiz)
{
	if (raiz == NULL)
	{
		return;
	}

	printf(" Raiz: %p - Chave: %d - Nivel: %d - Altura: %d - Pai: %p - Filho esquerdo: %p - Filho direito: %p\n", raiz, raiz->chave, raiz->nivel, raiz->altura, raiz->pai, raiz->esq, raiz->dir);
	exibeArvore(raiz->esq);
	exibeArvore(raiz->dir);
}

void liberaArvore(Arvore* raiz)
{
	if(raiz != NULL){
		liberaArvore(raiz->esq);
		liberaArvore(raiz->dir);
		free(raiz);
	}
}

void atualizaAltura(Arvore *raiz)
{
    while (raiz != NULL)
    {
        int altEsq = raiz->esq ? raiz->esq->altura + 1 : 0;
        int altDir = raiz->dir ? raiz->dir->altura + 1 : 0;
        raiz->altura = (altEsq > altDir) ? altEsq : altDir;
        raiz = raiz->pai;
    }
}