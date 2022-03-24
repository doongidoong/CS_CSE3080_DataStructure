#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_ROW 13
#define MAX_COL 17
#define EXIT_ROW 11
#define EXIT_COL 15
#define TRUE 1
#define FALSE 0

int maze[MAX_ROW][MAX_COL];
int mark[MAX_ROW][MAX_COL];

typedef struct {
  short int row;
  short int col;
  short int dir;
} element;
element stack[MAX_STACK_SIZE];

typedef struct {
  short int vert;
  short int horiz;
} offsets;
offsets move[8];

int top;

void push(element);
element pop();
void stackFull();
element stackEmpty();
void path();

void main() {

  int i, j;

  /* initialize maze */
  int maze_values[MAX_ROW][MAX_COL] = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                        { 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
                                        { 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
                                        { 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
                                        { 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1 },
                                        { 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
                                        { 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1 },
                                        { 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                        { 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1 },
                                        { 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
                                        { 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
                                        { 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
                                        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
  memcpy(maze, maze_values, sizeof(int) * MAX_ROW * MAX_COL);

  /* initialize mark */
  for(i = 0; i < MAX_ROW; i++) {
    for(j = 0; j < MAX_ROW; j++) {
      mark[i][j] = 0;
    }
  }

  /* initialize move */
  move[0].vert = -1; move[0].horiz =  0;    // N
  move[1].vert = -1; move[1].horiz =  1;    // NE
  move[2].vert =  0; move[2].horiz =  1;    // E
  move[3].vert =  1; move[3].horiz =  1;    // SE
  move[4].vert =  1; move[4].horiz =  0;    // S
  move[5].vert =  1; move[5].horiz = -1;    // SW
  move[6].vert =  0; move[6].horiz = -1;    // W
  move[7].vert = -1; move[7].horiz = -1;    // NW

  /* run path algorithm */
  path();
}

void push(element item) {
  /* add an item to the global stack */
  if(top >= MAX_STACK_SIZE - 1)
    stackFull();
  stack[++top] = item;
}

element pop() {
  /* return the top element from the stack */
  if(top == -1)
    return stackEmpty();  /* error handler */
  return stack[top--];
}

void stackFull() {
  fprintf(stderr, "stack is fuill, cannot add element.\n");
  exit(EXIT_FAILURE);
}

element stackEmpty() {
  element e;
  e.row = -1; e.col = -1; e.dir = -1;
  return e;
}

void path() {
  /* output a patch through the maze if such a path exists */
  int i, row, col, nextRow, nextCol, dir, found = FALSE;
  element position;
  mark[1][1] = 1; top = 0;
  stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

  while(top > -1 && !found) {
    position = pop();
    row = position.row; col = position.col; dir = position.dir;
    while(dir < 8 && !found) {
      /* move in direction dir */
      nextRow = row + move[dir].vert;
      nextCol = col + move[dir].horiz;
      if(nextRow == EXIT_ROW && nextCol == EXIT_COL)
        found = TRUE;
      else if(!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
        mark[nextRow][nextCol] = 1;
        position.row = row; position.col = col;
        position.dir = ++dir;
        push(position);
        row = nextRow; col = nextCol; dir = 0;
      }
      else ++dir;
    }
  }

  if(found) {
    printf("The path is: \n");
    printf("row col\n");
    for(i = 0; i <= top; i++) 
      printf("%2d%5d\n", stack[i].row, stack[i].col);
    printf("%2d%5d\n", row, col);
    printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
  }
  else printf("The maze does not have a path.\n");
}

