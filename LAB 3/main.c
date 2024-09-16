#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

typedef struct arvore Arvore;
struct arvore {
	int chave;
	Arvore* dir;
	Arvore* esq;
};

Arvore* criaArvore(int chave);
void insereArvoreNivel(Arvore** raiz, int chave);
void exibeArvore(Arvore* raiz);

int main(void) {
	int arr[] = { 10,5,15,3,7,13,20,1,4,6 };
	Arvore* raiz = NULL;
	for (int i = 0; i < 10; i++) {
		insereArvoreNivel(&raiz, arr[i]);
	}
	exibeArvore(raiz);
}

void insereArvoreNivel(Arvore** raiz, int chave) {
	if(*raiz == NULL){
		*raiz = criaArvore(chave);
		return;
	}
	else{
		Arvore** fila = (Arvore**)malloc(sizeof(Arvore*)*10);
		int inicio = 0, final = 0;
		fila[final] = *raiz;
		final++;
		while(inicio < final){
			Arvore* arvAtual = fila[inicio];
			inicio++;
			if(!arvAtual->esq){
				arvAtual->esq = criaArvore(chave);
				free(fila);
				return;
			}
			else{
				fila[final] = arvAtual->esq;
				final++;
			}
			if(!arvAtual->dir){
				arvAtual->dir = criaArvore(chave);
				free(fila);
				return;
			}
			else{
				fila[final] = arvAtual->dir;
				final++;
			}
		}
		free(fila);
	}
}

Arvore* criaArvore(int chave) {
	Arvore* a = (Arvore*)malloc(sizeof(Arvore));
	if (a == NULL) return NULL;
	a->chave = chave;
	a->dir = NULL;
	a->esq = NULL;
	return a;
}


void exibeArvore(Arvore* raiz) {
	if (raiz == NULL) {
		return;
	}
	printf("%d ", raiz->chave);
	exibeArvore(raiz->esq);
	exibeArvore(raiz->dir);
}