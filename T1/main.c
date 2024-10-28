#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 1321

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
        hash = ((hash << 5) + hash) + (cpf[i] - '0');
    }
    return hash % TAMANHO;
}

int hashSecundaria(char** hashTable, char* cpf) {
    int idx = hashCPF(cpf);
    int i = 0;
    while (hashTable[(idx + i * i) % TAMANHO] != NULL) {
        i++;
    }
    return (idx + i * i) % TAMANHO;
}

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
        int idx = hashCPF(cpf);
        int tentativas = 0;

        while (hashTable[idx] != NULL) {
            colisoes++;
            idx = hashSecundaria(hashTable, cpf);
            tentativas++;
        }

        hashTable[idx] = strdup(cpf);
        armazenados++;
    }

    printf("CPFs armazenados:\n");
    int contadorCpfs = 0;
    for (int i = 0; i < TAMANHO; i++) {
        if (hashTable[i] != NULL) {
            contadorCpfs++;
            printf("%d CPF armazenado = %s\n", contadorCpfs, hashTable[i]);
        }
    }

    printf("Total de CPFs armazenados: %d\n", armazenados);
    printf("Colisões: %d\n", colisoes);

    fclose(arquivoCpfs);

    for (int i = 0; i < TAMANHO; i++) {
        free(hashTable[i]);
    }
    free(hashTable);

    return 0;
}
