//============================================================================//
// ex010: dense representation of a matrix                                    //
//============================================================================//
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **m, int rows, int cols) {
  int i, j;
  for(i=0; i<rows; i++) {
    for(j=0; j<cols; j++) {
      printf("%3d ", m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void transpose(int **m, int rows, int cols) {
  int i, j, temp;
  for(i=0; i<rows; i++) {
    for(j=i+1; j<cols; j++) {
      // swap m[i][j] and m[j][i]
      temp = m[i][j];
      m[i][j] = m[j][i];
      m[j][i] = temp;
    }
  }
}

void main() {

  int i, j;
  int **matrix;
  matrix = malloc(6 * sizeof(*matrix));
  for(i=0; i<6; i++) {
    matrix[i] = malloc(6 * sizeof(**matrix));
    for(j=0; j<6; j++) {
      matrix[i][j] = 0;
    }
  }

  matrix[0][0] = 15;
  matrix[0][3] = 22;
  matrix[0][5] = -15;
  matrix[1][1] = 11;
  matrix[1][2] = 3;
  matrix[2][3] = -6;
  matrix[4][0] = 91;
  matrix[5][2] = 28;

  printMatrix(matrix, 6, 6);
  transpose(matrix, 6, 6);
  printMatrix(matrix, 6, 6);

  for(i=0; i<6; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

  





