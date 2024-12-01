#include <stdio.h>
#include <stdlib.h>

#define FOLHA 1
#define MAX_CHAVES 3
#define MAX_PONTEIROS 4

typedef struct No {
    int chaves[MAX_CHAVES];
    struct No* ponteiros[MAX_PONTEIROS];
    int ehFolha;
    int numChaves;
    struct No* pai;
} No;

int fezSplit = 0;

No* criaNo(int folha, No* pai);
No* cisaoFolha(No* raiz, int valorMeio);
No* insereChave(No* raiz, int chave, int ehFolha);
No* buscarChave(No* no, int chave);
int encontraIndexInsercaoPonteiro(No* raiz, int chave);
int encontraIndexInsercaoFolha(No* raiz, int chave);
int verificaEhFolha(No* raiz);
void swapNo(No* raiz);
No* excluirChave(No* raiz, int chave);

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
    int i = raiz->numChaves;
    while (i > 0 && raiz->chaves[i-1] > chave) {
        raiz->chaves[i] = raiz->chaves[i-1]; // Desloca a chave maior
        raiz->ponteiros[i+1] = raiz->ponteiros[i];
        i--;
    }
    return i;
}
int encontraIndexInsercaoPonteiro(No* raiz, int chave){
    int i = raiz->numChaves;
    while (i > 0 && raiz->chaves[i-1] > chave)i--;
    return i;
}


int verificaEhFolha(No* raiz){
    for(int i = 0; i < MAX_PONTEIROS; i++){
        if(raiz->ponteiros[i]) return !FOLHA;
    }
    return FOLHA;
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

    else if(raiz->numChaves>0){
        int idxPonteiro = encontraIndexInsercaoPonteiro(raiz, chave);
        int ponteiroEhFolha = verificaEhFolha(raiz->ponteiros[idxPonteiro]);

        No* retorno = insereChave(raiz->ponteiros[idxPonteiro], chave, ponteiroEhFolha);


        if(fezSplit){
            fezSplit=0;
            No* temp = raiz;
            while(temp->pai!=NULL)temp=temp->pai;
            return temp;
        }
        else if(retorno == raiz->pai)return raiz->pai;
       
    }
    return raiz;
}

No* insereChaveInterno(No* raiz, int chave){
    int idxFolha = encontraIndexInsercaoFolha(raiz, chave);
    raiz->chaves[idxFolha] = chave;
    raiz->numChaves++;
    if(raiz->numChaves == 3){
        return cisaoFolha(raiz, raiz->chaves[1]);
    }
    return raiz;
}


No* cisaoFolha(No* raiz, int valorMeio){
    if(!(raiz->pai)){
        No* novaRaiz = criaNo(!FOLHA, NULL);
        novaRaiz->chaves[0] = valorMeio;
        
        No** filhoMenor = &(novaRaiz->ponteiros[0]);
        *filhoMenor = insereChave(NULL, raiz->chaves[0], raiz->ehFolha);
        (*filhoMenor)->pai = novaRaiz;
        novaRaiz->ponteiros[1] = raiz;

        if(!raiz->ehFolha){
            (*filhoMenor)->chaves[0] = raiz->chaves[0];
            swapNo(raiz);
           
            (*filhoMenor)->ponteiros[0]=raiz->ponteiros[0];
            (*filhoMenor)->ponteiros[1]=raiz->ponteiros[1];
            raiz->ponteiros[0]->pai=(*filhoMenor);
            raiz->ponteiros[1]->pai=(*filhoMenor);
            (*filhoMenor)->numChaves++;
          
            raiz->ponteiros[0]=raiz->ponteiros[2];
            raiz->ponteiros[1]=raiz->ponteiros[3];
            raiz->ponteiros[2]=raiz->ponteiros[3]=NULL;

            fezSplit = 1;
        }
        swapNo(raiz);
        novaRaiz->numChaves++;
        raiz->pai = novaRaiz;
        return novaRaiz;
    }
    else{

        int idx = encontraIndexInsercaoPonteiro(raiz->pai, raiz->chaves[0])+1;

        No* filhoMenor = criaNo(FOLHA, raiz->pai);
        filhoMenor = insereChave(filhoMenor, raiz->chaves[0], FOLHA);
        filhoMenor->ehFolha = raiz->ehFolha;
        raiz->pai->ponteiros[idx] = filhoMenor;
        swapNo(raiz);
        int temp = raiz->pai->ponteiros[idx]->chaves[0];
        raiz->pai->ponteiros[idx]->chaves[0] = raiz->pai->ponteiros[idx-1]->chaves[0];
        raiz->pai->ponteiros[idx]->chaves[1] = raiz->pai->ponteiros[idx-1]->chaves[1];
        raiz->pai->ponteiros[idx-1]->chaves[0] = temp;
        raiz->pai->ponteiros[idx]->numChaves++;
        raiz->pai->ponteiros[idx-1]->numChaves--;

        if(!raiz->ehFolha){
            swapNo(filhoMenor);
                   
            filhoMenor->ponteiros[0]=raiz->ponteiros[2];     
            filhoMenor->ponteiros[1]=raiz->ponteiros[3];
            raiz->ponteiros[2]->pai=filhoMenor;
            raiz->ponteiros[3]->pai=filhoMenor;
          
            raiz->ponteiros[2]=raiz->ponteiros[3]=NULL;
        }
        
        raiz->pai->ponteiros[idx] = filhoMenor;

        insereChaveInterno(raiz->pai, valorMeio);

        return raiz;
    }
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

No* buscarChave(No* no, int chave){
    if(!no) return NULL;
    if(no->ehFolha){
        if(no->chaves[0] == chave || no->chaves[1] == chave){
            return no;
        }
        else return NULL;
    }
    if(chave < no->chaves[0]){
        return buscarChave(no->ponteiros[0], chave);
    }
    else if(no->chaves[1] == -1 || chave < no->chaves[1]){
        return buscarChave(no->ponteiros[1], chave);
    }
    return buscarChave(no->ponteiros[2], chave);
}

No* excluirChave(No* raiz, int chave) {
    No* no = buscarChave(raiz, chave);
    if (!no) return raiz; // Chave não encontrada
    
    // Remover a chave do nó
    int i;
    for (i = 0; i < no->numChaves; i++) {
        if (no->chaves[i] == chave) break;
    }
    for (; i < no->numChaves - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
    }
    no->chaves[no->numChaves - 1] = -1;
    no->numChaves--;
    // Verificar se precisa de redistribuição ou fusão
    if (no->numChaves < 1 && no->pai) {
        No* pai = no->pai;
        int idx;
        for (idx = 0; idx <= pai->numChaves; idx++) {
            if (pai->ponteiros[idx] == no) break;
        }

        // Tentar redistribuir
        if (idx > 0 && pai->ponteiros[idx - 1]->numChaves > 1) {

            No* irmaoEsq = pai->ponteiros[idx - 1];
            no->chaves[0] = pai->chaves[idx - 1];
            no->numChaves++;
            pai->chaves[idx - 1] = irmaoEsq->chaves[irmaoEsq->numChaves - 1];
            irmaoEsq->chaves[irmaoEsq->numChaves - 1] = -1;
            irmaoEsq->numChaves--;
        }
        else if (idx < pai->numChaves && pai->ponteiros[idx + 1]->numChaves > 1) {

            No* irmaoDir = pai->ponteiros[idx + 1];
            no->chaves[no->numChaves] = pai->chaves[idx];
            no->numChaves++;
            pai->chaves[idx] = irmaoDir->chaves[0];
            for (int j = 0; j < irmaoDir->numChaves - 1; j++) {
                irmaoDir->chaves[j] = irmaoDir->chaves[j + 1];
            }
            irmaoDir->chaves[irmaoDir->numChaves - 1] = -1;
            irmaoDir->numChaves--;
        }
        else {
            // Fazer fusão
            if (idx > 0) {
                No* irmaoEsq = pai->ponteiros[idx - 1];
                irmaoEsq->chaves[irmaoEsq->numChaves] = pai->chaves[idx - 1];
                irmaoEsq->numChaves++;
                for (int j = 0; j < no->numChaves; j++) {
                    irmaoEsq->chaves[irmaoEsq->numChaves + j] = no->chaves[j];
                }
                irmaoEsq->numChaves += no->numChaves;
                free(no);
                for (int j = idx - 1; j < pai->numChaves - 1; j++) {
                    pai->chaves[j] = pai->chaves[j + 1];
                    pai->ponteiros[j + 1] = pai->ponteiros[j + 2];
                }
                pai->chaves[pai->numChaves - 1] = -1;
                pai->ponteiros[pai->numChaves] = NULL;
                pai->numChaves--;
            }
            else {
                No* irmaoDir = pai->ponteiros[idx + 1];
                no->chaves[no->numChaves] = pai->chaves[idx];
                no->numChaves++;
                for (int j = 0; j < irmaoDir->numChaves; j++) {
                    no->chaves[no->numChaves + j] = irmaoDir->chaves[j];
                }
                no->numChaves += irmaoDir->numChaves;
                free(irmaoDir);
                for (int j = idx; j < pai->numChaves - 1; j++) {
                    pai->chaves[j] = pai->chaves[j + 1];
                    pai->ponteiros[j + 1] = pai->ponteiros[j + 2];
                }
                pai->chaves[pai->numChaves - 1] = -1;
                pai->ponteiros[pai->numChaves] = NULL;
                pai->numChaves--;
            }
        }
    }

    // Ajuste da raiz, se necessário
    if (raiz->numChaves == 0 && !raiz->ehFolha) {
        No* novaRaiz = raiz->ponteiros[0];
        novaRaiz->pai = NULL;
        free(raiz);
        raiz = novaRaiz;
    }

    return raiz;
}



No* removerChave(No* raiz, int chave) {
    if (!raiz) return NULL; // Chave não encontrada
    
    if(raiz->ehFolha){
        int i;
        for (i = 0; i < raiz->numChaves; i++) {
            if (raiz->chaves[i] == chave) break;
        }
        for (; i < raiz->numChaves - 1; i++) {
            raiz->chaves[i] = raiz->chaves[i + 1];
        }
        raiz->chaves[raiz->numChaves - 1] = -1;
        raiz->numChaves--;
    }
    else{
        int idxPonteiro = raiz->numChaves;
        while(chave > raiz->chaves[idxPonteiro] && idxPonteiro > 0){
            idxPonteiro--;
        }
        raiz = removerChave(raiz->ponteiros[idxPonteiro], chave);
        if(raiz->ponteiros[idxPonteiro]->numChaves < 1){
            if(idxPonteiro == 1){
                if(raiz->ponteiros[idxPonteiro - 1]->numChaves == 2){
                    redistribuir;
                }                
                else if(raiz->ponteiros[idxPonteiro + 1]->numChaves == 2){
                    redistribuir;
                }
                else{
                    merge
                }
            }
            else if(idxPonteiro == 2){
                if(raiz->ponteiros[idxPonteiro - 1]->numChaves == 2){
                    redistribuir;
                }
                else{
                    merge
                }
            else{
                if(raiz->ponteiros[idxPonteiro + 1]->numChaves == 2){
                    redistribuir;
                }
                else{
                    merge
                }
            }
            }
        }
    }
    return raiz;
}


int main() {
    No* raiz = NULL;
    
    raiz = insereChave(raiz, 10,FOLHA);
    raiz = insereChave(raiz, 15, FOLHA);
    raiz = insereChave(raiz, 13, FOLHA);
    raiz = insereChave(raiz, 5, !FOLHA);
    raiz = insereChave(raiz, 20, !FOLHA);
    // raiz = insereChave(raiz, 25, !FOLHA);
    // raiz = insereChave(raiz, 26, !FOLHA);
    // raiz = insereChave(raiz, 27, !FOLHA);
    // raiz = insereChave(raiz, 28, !FOLHA);

    No* encontraChaveExistente = buscarChave(raiz, 15);
    No* encontraChaveNaoExistente = buscarChave(raiz, 30);

    imprimeArvore(raiz);

    removerChave(raiz, 13);
    printf("\napos remocao:\n\n");
    imprimeArvore(raiz);

    printf("\nTeste encontrar chave existente: %p\n", encontraChaveExistente);
    
    printf("Teste encontrar chave nao existente: %p\n", encontraChaveNaoExistente);

    return 0;
}