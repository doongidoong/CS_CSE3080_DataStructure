#include <stdio.h>
#include <stdlib.h>

#define INVALID_KEY -1

typedef struct {
  int key;
} element;
element *stacks[2];
int top[2] = {-1, -1};
int capacity[2] = {1, 1};
int num_copy = 0;
int count = 0;

void push(int stackIdx, element item);
element pop(int stackIdx);
void stackFull(int stackIdx);
element stackEmpty();
void printStack(int stackIdx);

void main() {

  int i, num_items = 100;

  /* set initial capacity of stacks and allocate memory */ 
  stacks[0] = (element*)malloc(sizeof(element)*capacity[0]);
  stacks[1] = (element*)malloc(sizeof(element)*capacity[1]);

  for(i=0; i<num_items; i++) {
    element e;
    e.key = i;
    push(0, e);
    push(1, e);
  }

  printf("number of items inserted: %d\n", num_items * 2);
  printf("number of memory copies: %d\n", num_copy);
}

void push(int stackIdx, element item) {
  if(top[stackIdx] >= capacity[stackIdx]-1) stackFull(stackIdx);
  stacks[stackIdx][++top[stackIdx]] = item;
}

element pop(int stackIdx) {
  if(top[stackIdx] == -1) return stackEmpty();
  return stacks[stackIdx][top[stackIdx]--];
}

void stackFull(int stackIdx) {
  count++;
  printf("number of stack full called: %d\n", count);  
  element* temp = stacks[stackIdx];
  capacity[stackIdx]++;
  stacks[stackIdx] = (element*)realloc(stacks[stackIdx], sizeof(element)*capacity[stackIdx]); 
  if(temp != stacks[stackIdx]) {
    printf("MEMORY COPY %p -> %p\n", temp, stacks[stackIdx]);
    num_copy++;
  }
}

element stackEmpty() {
  element e;
  e.key = INVALID_KEY;
  return e;
}

void printStack(int stackIdx) {

  int i;
  printf("stacks[%d] - address: %p, capacity: %d\n", stackIdx, stacks[stackIdx], capacity[stackIdx]);
  for(i=0; i<=top[stackIdx]; i++) {
    printf("%d ", stacks[stackIdx][i].key);
  }
  printf("\n");
}


