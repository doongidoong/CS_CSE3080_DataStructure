//============================================================================//
// ex012: a faster transpose function for sparse representation of a matrix   //
//============================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERMS 101
#define MAX_COL 10

typedef struct {
  int row;
  int col;
  int value;
} term;

void printMatrix(term*);
void fast_transpose(term*, term*);

void main() {
  
  term a[MAX_TERMS], b[MAX_TERMS];
  
  a[0].row = 6; a[0].col = 6; a[0].value = 8;  // # of rows, # or cols, # of terms
  a[1].row = 0; a[1].col = 0; a[1].value = 15;
  a[2].row = 0; a[2].col = 3; a[2].value = 22;
  a[3].row = 0; a[3].col = 5; a[3].value = 15;
  a[4].row = 1; a[4].col = 1; a[4].value = 11;
  a[5].row = 1; a[5].col = 2; a[5].value = 3;
  a[6].row = 2; a[6].col = 3; a[6].value = 6;
  a[7].row = 4; a[7].col = 0; a[7].value = 91;
  a[8].row = 5; a[8].col = 2; a[8].value = 28;

  b[0].row = 0; b[0].col = 0; b[0].value = 0;

  printMatrix(a);
  clock_t start_time = clock();
  fast_transpose(a, b);
  clock_t end_time = clock();
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

void fast_transpose(term a[], term b[]) {
  
  /* complete this function! */
  /* the time complexity of this function should be O(columns + elements) */
  /* b is set to the transpose of a */
  int row_terms[MAX_COL], starting_pos[MAX_COL];
  int i, j, num_cols = a[0].col, num_terms = a[0].value;
  b[0].row = num_cols; b[0].col = a[0].row;
  b[0].value = num_terms;
  if(num_terms > 0) { /* non-zero matrix */ 
    for(i=0; i<num_cols; i++) row_terms[i] = 0; 
    for(i=1; i<=num_terms; i++) row_terms[a[i].col]++; // 먼저 a의 열의 개수를 모두 B의 행 배열에 넣어준다
    starting_pos[0] = 1;  
    for(i=1; i<num_cols; i++) // 그 뒤 각 B의 인덱스(열)에 값에 따른 시작점을 정하기 위해
    starting_pos[i] = starting_pos[i-1] + row_terms[i-1]; //이전까지의 시작점과 해당 열의 원소 개수를 더해준다
    for(i=1; i<=num_terms; i++) {
      j = starting_pos[a[i].col]++;//이제 a의 원소를 차례차례 보면서 시작점을 j에 넣어주고 시작점을 하나 증가시킨다
      b[j].row = a[i].col; //그 이유는 만약 col:pos/ 0:2,1:4,2:6일 경우 a[i]의 컬럼이 1이라면 j에 4가 들어가게 되고 b[4]에 a[i]의 값을 전치해서 넣는다
      b[j].col = a[i].row; //하지만 여기에서 ++를 시켜주지 않을 경우 칼럼이 1일 때 해당 값에 덮어쓰기가 된다. 따라서 다음칸을 가르키도록 
      b[j].value = a[i].value; // 1을 더해준다.
    }
  }
}



