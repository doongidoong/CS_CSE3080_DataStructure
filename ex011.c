//============================================================================//
// ex011: sparse representation of a matrix                                   //
//============================================================================//
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
typedef struct {
  int row;
  int col;
  int value;
} term;

void printMatrix(term*);
void transpose(term*, term*);

void main() {
  
  term a[MAX_TERMS], b[MAX_TERMS];
  
  a[0].row = 6; a[0].col = 6; a[0].value = 8;  // # of rows, # or cols, # of terms
  a[1].row = 0; a[1].col = 0; a[1].value = 15;
  a[2].row = 0; a[2].col = 3; a[2].value = 22;
  a[3].row = 0; a[3].col = 5; a[3].value = -15;
  a[4].row = 1; a[4].col = 1; a[4].value = 11;
  a[5].row = 1; a[5].col = 2; a[5].value = 3;
  a[6].row = 2; a[6].col = 3; a[6].value = -6;
  a[7].row = 4; a[7].col = 0; a[7].value = 91;
  a[8].row = 5; a[8].col = 2; a[8].value = 28;

  b[0].row = 0; b[0].col = 0; b[0].value = 0;

  printMatrix(a);
  transpose(a, b);
  printMatrix(b);
}

void printMatrix(term *m) {

  int iter = 1, i, j;
  int rows = m[0].row;
  int cols = m[0].col;
  int num_terms = m[0].value;

  for(i=0; i<rows; i++) {
    for(j=0; j<cols; j++) {
      if(iter <= num_terms && m[iter].row == i && m[iter].col == j) {
        printf("%3d ", m[iter].value);
        iter++;
      } else {
        printf("%3d ", 0);
      }
    }
    printf("\n");
  } 
  printf("\n");
}

void transpose(term *a, term *b) {

  /* complete this function! */
  /* the time complexity of this function should be O(num_columns x num_elements) */
  int n, i, j, currentb;
  n = a[0].value; /* total number of elements */
  b[0].row = a[0].col; /* rows in b = columns in a */
  b[0].col = a[0].row; /* columns in b = rows in a */
  b[0].value = n;
  if (n > 0) { /* non-zero matrix */
    currentb = 1;
    for(i = 0; i < a[0].col; i++)
    /* transpose by the columns in a */
      for(j = 1; j <= n; j++) 
      /* find elements from the current column */
        if(a[j].col == i) {
        /* element is in current column, add it to b */
          b[currentb].row = a[j].col;
          b[currentb].col = a[j].row;
          b[currentb].value = a[j].value;
          currentb++;
        }
  }
}























