#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int, int);

void main() {
    int i, j;
    int **matrix;

    matrix = make2dArray(5, 5); //이차원배열

    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            matrix[i][j] = i*5 + j + 1;
            printf("%p: %2d ", &matrix[i][j], matrix[i][j]);
        }
        printf("\n");
    }

    /* free memory */
    for(i = 0; i < 5; i++) 
        free(matrix[i]);
    free(matrix);
}

int** make2dArray(int rows, int cols) {

    int **x, i;
    printf("%d %d\n",rows,cols);
    /* allocate memory for row pointers */
 
    x = malloc(rows*sizeof(*x)); // *(포인터의 포인터) = 포인터 * rows
    printf("*x = %lu\n", sizeof(*x));//포인터의 크기
    printf("**x = %lu\n", sizeof(**x)); //int의 크기
    printf("x allocated at address %p\n", x);

    /* allocate memory for each row */
    for(i = 0; i < rows; i++)  {
        x[i] = malloc(cols*sizeof(**x));
        printf("x[%2d] allocated at address %p\n", i, x[i]);
    }
       
    return x;
}    
