#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 10    // maximum stack size
#define INVALID_KEY -1

typedef struct {
  int key;
  /* other fields if necessary */
} element;
element stack[MAX_STACK_SIZE];
int top = -1;   // if top is -1, it means the stack is empty

void push(element);
element pop();
void stackFull();
element stackEmpty();
//void printStack();

void main() {

  int i;
  element e;

  for(i = 0; i < 15; i++) {
    e.key = i;
    push(e);
    printf("key %d inserted into the stack.\n", e.key);
  }  

  for(i = 0; i < 5; i++) {
    e = pop();
    printf("key %d deleted from the stack.\n", e.key);
  }
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
  fprintf(stderr, "stack is full, cannot add element.\n");
  exit(EXIT_FAILURE);
}

element stackEmpty() {
  element e;
  e.key = INVALID_KEY;
  return e;
}



