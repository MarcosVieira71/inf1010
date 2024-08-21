//Marcos Vieira | Matrícula:2320466
//Julia Zibordi | Matrícula:2320934

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define SIZE 6

int binarySearch(int target, int* arr, int arrSize);
void fillArray(int size, int* arr);
void quickSort(int arr[], int low, int high);
void swap(int* arr, int begin, int end);
int partition(int* arr, int begin, int end);


int main(void) {

    int arr[SIZE];

    fillArray(SIZE, arr);
    clock_t t = clock();
    quickSort(arr, 0, SIZE-1);

    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", arr[i]);
        int randomNumber = rand() % (SIZE + 1);
        if (binarySearch(randomNumber, arr, SIZE) == -1) {
            //printf("%d\n", randomNumber);
        }
    }
    t = clock() - t;

    printf("Tempo de execucao: %lf\n", (float)(t) / (CLOCKS_PER_SEC));
    return 0;
}

void fillArray(int size, int* arr) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % (SIZE + 1);
    }
}

int binarySearch(int target, int* arr, int arrSize) {
    int begin = 0;
    int end = arrSize - 1;
    while (begin <= end) {
        int mid = (end + begin) / 2;
        if (arr[mid] > target) end = mid - 1;
        else begin = mid + 1;
        if (arr[mid] == target) return mid;
    }
    return -1;
}

int partition(int* arr, int begin, int end) {
    int pivot = arr[end];
    int i = begin - 1;
    for(int j = begin; j <= end - 1; j++){
        if(arr[j] <= pivot){
            i+=1;
            swap(arr, i, j);
        }
    }
    swap(arr, i+1, end);
    return i+1;
}


void swap(int* arr, int begin, int end) {
    int aux = arr[begin];
    arr[begin] = arr[end];
    arr[end] = aux;
}


void quickSort(int arr[], int begin, int end) {
    if (begin < end) {
        int partitionIdx = partition(arr, begin, end);

        quickSort(arr, begin, partitionIdx - 1);
        quickSort(arr, partitionIdx + 1, end);
    }
}
