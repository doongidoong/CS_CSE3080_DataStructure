#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100
#define MAX_VALUE 100

void init_list(int *list, int n) {
    int i;
    for(i=0; i<n; i++) {
        list[i] = rand() % MAX_VALUE + 1;
    }
}

void print_list(int *list, int n) {
    int i;
    for(i=0; i<n; i++) {
        printf("%3d ", list[i]);
    }
    printf("\n");
}

void insertion_sort(int *A, int n) {
    int i, j, tmp;

    for(i=1; i<n; i++) {
        tmp = A[i];
        j = i;
        while( (j > 0 ) && ( tmp < A[j-1] ) ) {
            A[j] = A[j-1];
            j--;
        }
        A[j] = tmp;
    }
}

void selection_sort(int *A, int n) {
    int i, j, cur, tmp;

    for(i=0; i<n-1; i++) {
        cur = i;
        for(j=i+1; j<n; j++) {
            if(A[j] < A[cur]) cur = j;
        }

        tmp = A[i];
        A[i] = A[cur];
        A[cur] = tmp;
    }
}

void bubble_sort(int *A, int n) {
    int i, j, tmp;

    for(i=0; i<n-1; i++) {
        for(j=n-1; j>i; j--) {
            if(A[j] < A[j-1]) {
                tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;
            }
        }
    }
}

void main() {
    int i;
    int list[MAX_NUMBERS];

    srand(time(NULL));

    init_list(list, 10);
    print_list(list, 10);
    //insertion_sort(list, 10);
    //selection_sort(list, 10);
    bubble_sort(list, 10);
    print_list(list, 10);
}

