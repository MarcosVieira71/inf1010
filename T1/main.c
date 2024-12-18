#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 29

char** inicializaHashTable(){
    char** hashTable = (char**)malloc(sizeof(char*) * TAMANHO);
    for (int i = 0; i < TAMANHO; i++) {
        hashTable[i] = NULL;
    }
    return hashTable;
}

int hashCPF(char* cpf){
    unsigned int hash = 0;
    for(int i = 0; cpf[i] != '\0'; i++){
        hash = (hash * 31) ^ (cpf[i] - '0');
    }
    return hash % TAMANHO;
}

int hashSecundaria(char* cpf) {
    unsigned int hash = 0;
     for (int i = 0; cpf[i] != '\0'; i++) {
        hash = (hash * 37) + (cpf[i] - '0');  
    }
    return 1 + (hash % (TAMANHO - 1)); 
}

int main(void){
    char** hashTable = inicializaHashTable();
    FILE* arquivoCpfs = fopen("cpfs.txt", "r");
        if (arquivoCpfs == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char cpf[12];
    int cont = 0;
    int colisoes = 0;

    while (fscanf(arquivoCpfs, "%11s", cpf) != EOF && cont < 20){ 
        int idx = hashCPF(cpf);

        while(hashTable[idx] != NULL) {
            colisoes++;
            idx = (idx + hashSecundaria(cpf))% TAMANHO;
        }
        
        hashTable[idx] = strdup(cpf);
        cont++;
    }

    for(int i = 0; i < TAMANHO; i++){
        printf("%dº CPF armazenado = %s\n",i,  hashTable[i]);
    }

    printf("Colisões: %d\n", colisoes);
    fclose(arquivoCpfs);

    for(int i = 0; i < TAMANHO; i++) {
        free(hashTable[i]);
    }

    free(hashTable);
}