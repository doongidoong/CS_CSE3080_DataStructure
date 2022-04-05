#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
typedef enum {head, entry} tagfield;
struct entry_node {
  int row;
  int col;
  int value;
};
struct matrix_node {
  struct matrix_node *down;
  struct matrix_node *right;
  tagfield tag;
  union {
    struct matrix_node *next;
    struct entry_node entry;
  } u;
};
typedef struct matrix_node *matrix_pointer;
matrix_pointer hdnode[MAX_SIZE];

matrix_pointer new_node();
matrix_pointer mread();
void mwrite(matrix_pointer node);
void merase(matrix_pointer *node);

void main() {

  matrix_pointer m = mread();
  mwrite(m); 
  merase(&m);

}

matrix_pointer new_node() {
  matrix_pointer n = (matrix_pointer)malloc(sizeof(struct matrix_node));
  return n;
}

matrix_pointer mread() {
  
  int num_rows, num_cols, num_terms, num_heads, i;
  int row, col, value, current_row;
  matrix_pointer temp, last, node;

  printf("Enter the number of rows, columns and number of nonzero terms:\n");
  scanf("%d %d %d", &num_rows, &num_cols, &num_terms);

  num_heads = (num_cols > num_rows) ? num_cols : num_rows;
  
  node = new_node(); 
  node->tag = entry;
  node->u.entry.row = num_rows;
  node->u.entry.col = num_cols;
  
  if(!num_heads) node->right = node;
  else {
    for(i=0; i<num_heads; i++) {
      temp = new_node();
      hdnode[i] = temp;
      hdnode[i]->tag = head;
      hdnode[i]->right = temp;
      hdnode[i]->u.next = temp;
    }
    current_row = 0; 
    last = hdnode[0];    

    for(i=0; i<num_terms; i++) {
      printf("Enter row, column and value:\n");
      scanf("%d %d %d", &row, &col, &value);
      if(row > current_row) {
        last->right = hdnode[current_row];
        current_row = row;
        last = hdnode[row];
      }
      temp = new_node();
      temp->tag = entry;
      temp->u.entry.row = row;
      temp->u.entry.col = col;
      temp->u.entry.value = value;
      last->right = temp;
      last = temp;
      hdnode[col]->u.next->down = temp;
      hdnode[col]->u.next = temp;
    }

    // close last row
    last->right = hdnode[current_row];
    // close all column lists
    for(i=0; i<num_cols; i++)
      hdnode[i]->u.next->down = hdnode[i];
    // link all head nodes together
    for(i=0; i<num_heads-1; i++)
      hdnode[i]->u.next = hdnode[i+1];
    hdnode[num_heads-1]->u.next = node;
    node->right = hdnode[0];
  }
  return node;
}

void mwrite(matrix_pointer node) {
  int i;
  matrix_pointer temp;
  matrix_pointer head = node->right;

  printf("\nnumRows = %d, numCols = %d\n", node->u.entry.row, node->u.entry.col);
  printf("The matrix by row, column, and value:\n\n");
  for(i=0; i<node->u.entry.row; i++) {
    for(temp = head->right; temp != head; temp = temp->right)
      printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
    head = head->u.next;
  }
}

void merase(matrix_pointer *node) {
  int i, num_heads;
  matrix_pointer x, y, head = (*node)->right;

  for(i=0; i<(*node)->u.entry.row; i++) {
    y = head->right;
    while(y != head) {
      x = y; y = y->right; free(x);
    }
    x = head; head = head->u.next; free(x);
  }

  y = head;
  while(y != *node) {
    x = y; y = y->u.next; free(x);
  }
  free(*node); *node = NULL;
}
