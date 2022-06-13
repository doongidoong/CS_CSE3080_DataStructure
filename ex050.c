#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100
#define MAX_VALUE 100


int partition(int *A, int left, int right) {
    int i, pivot, tmp;

    pivot = left;
    for(i = left; i < right; i++) {
        if(A[i] < A[right]) {
            tmp = A[i];
            A[i] = A[pivot];
            A[pivot] = tmp;
            pivot++;
        }
    }
    tmp = A[right];
    A[right] = A[pivot];
    A[pivot] = tmp;
    return pivot;
}

void quick_sort(int *A, int left, int right) {
    int pivot;

    if(right-left > 0) {
        pivot = partition(A, left, right);

        quick_sort(A, left, pivot-1);
        quick_sort(A, pivot+1, right);
    }
}

void init_list(int *list, int n) {
    int i;
    for(i=0; i<n; i++) {
        list[i] = rand() % MAX_VALUE + 1;
    }
}

void print_list(int* list, int n) {
    int i;
    for(i=0; i<n; i++) {
        printf("%3d ", list[i]);
    }
    printf("\n");
}

void main() {

    int i;
    int list[MAX_NUMBERS];

    srand(time(NULL));

    init_list(list, 10);
    print_list(list, 10);
    quick_sort(list, 0, 9);
    print_list(list, 10);
}