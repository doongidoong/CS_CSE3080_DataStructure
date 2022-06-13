#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100
#define MAX_VALUE 100

int buffer[MAX_NUMBERS];

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

void merge(int *A, int left, int middle, int right) {

    int i, i_left, i_right;

    for(i=0; i<(right-left+1); i++) {
        buffer[left+i] = A[left+i];
    }

    i_left = left;
    i_right = middle + 1;
    i = left;

    while( (i_left <= middle) && (i_right <= right) ) {
        if( buffer[i_left] < buffer[i_right] ) {
            A[i++] = buffer[i_left++];
        }
        else {
            A[i++] = buffer[i_right++];
        }
    }

    while(i_left <= middle) {
        A[i++] = buffer[i_left++];
    }
    while(i_right <= right) {
        A[i++] = buffer[i_right++];
    }
}

void merge_sort(int *A, int left, int right) {
    
    int middle;
    if(left < right) {
        middle = (left + right) / 2;
        merge_sort(A, left, middle);
        merge_sort(A, middle+1, right);
        
        merge(A, left, middle, right);
    }

}






void main() {
    int i;
    int list[MAX_NUMBERS];

    srand(time(NULL));

    init_list(list, 10);
    print_list(list, 10);
    merge_sort(list, 0, 9);
    print_list(list, 10);
}