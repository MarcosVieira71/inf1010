#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

typedef struct arvore Arvore;
struct arvore
{
	int chave;
	Arvore *dir;
	Arvore *esq;
};

Arvore *criaArvore(int chave);
void insereArvoreNivel(Arvore **raiz, int chave);
void exibeArvore(Arvore *raiz);

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
}

void insereArvoreNivel(Arvore **raiz, int chave)
{
	if (*raiz == NULL)
	{
		*raiz = criaArvore(chave);
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
				arvAtual->esq = criaArvore(chave);
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
				arvAtual->dir = criaArvore(chave);
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

Arvore *criaArvore(int chave)
{
	Arvore *a = (Arvore *)malloc(sizeof(Arvore));
	if (a == NULL)
		return NULL;
	a->chave = chave;
	a->dir = NULL;
	a->esq = NULL;
	return a;
}

void exibeArvore(Arvore *raiz)
{
	if (raiz == NULL)
	{
		return;
	}

	exibeArvore(raiz->esq);
	printf("%d\n", raiz->chave);
	exibeArvore(raiz->dir);
}