#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 1249

char** inicializaHashTable(void);
int hashCPF(char* cpf);
int hashSecundaria(int idx, int i);
int insereHash(char** hashTable, char* cpf, int* colisoes);
void liberaHashTable(char** hashTable);

int main(void) {
    char** hashTable = inicializaHashTable();
    FILE* arquivoCpfs = fopen("cpfs.txt", "r");
    if (arquivoCpfs == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char cpf[12];
    int colisoes = 0;
    int armazenados = 0;

    while (fscanf(arquivoCpfs, " %11s", cpf) != EOF) {
        insereHash(hashTable, cpf, &colisoes);
        armazenados++;
        if(armazenados % 100 == 0) printf("\n%d - Colisões: %d\n", armazenados, colisoes);
    }

    printf("CPFs armazenados:\n");
    int contadorCpfs = 0;
    int vazios = 0;
    for (int i = 0; i < TAMANHO; i++) {
        if (hashTable[i] != NULL) {
            contadorCpfs++;
        }
        else vazios++;
    }

    printf("Total de CPFs armazenados: %d\n", contadorCpfs);
    printf("Colisões: %d\n", colisoes);
    printf("Vazios: %d\n", vazios);


    fclose(arquivoCpfs);

    liberaHashTable(hashTable);

    return 0;
}

char** inicializaHashTable() {
    char** hashTable = (char**)malloc(sizeof(char*) * TAMANHO);
    for (int i = 0; i < TAMANHO; i++) {
        hashTable[i] = NULL;
    }
    return hashTable;
}

int hashCPF(char* cpf) {
    unsigned long hash = 5381;
    for (int i = 0; cpf[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (cpf[i]-'0');
    }
    return hash % TAMANHO;
}

int hashSecundaria(int idx, int i) {
    return (idx + i * i) % TAMANHO;
}

int insereHash(char** hashTable, char* cpf, int* colisoes) {
    int idx = hashCPF(cpf);
        int tentativas = 0;
        int i = 0;

        while (hashTable[idx] != NULL) {
            (*colisoes)++;
            i++;
            idx = hashSecundaria(hashCPF(cpf), i);
            tentativas++;
        }

        hashTable[idx] = strdup(cpf);

    return tentativas;
}

void liberaHashTable(char** hashTable) {
    for (int i = 0; i < TAMANHO; i++) {
        free(hashTable[i]);
    }
    free(hashTable);
}

