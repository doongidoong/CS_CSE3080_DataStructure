#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;
int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;

int eval();
precedence getToken(char*, int*);
void push(int);
int pop();
void stackFull();
int stackEmpty();

void main() {

  //sprintf(expr, "62/3-42*+");
  sprintf(expr, "12+7*");
  printf("expr: %s\n", expr);
  printf("eval: %d\n", eval());

}

int eval() {

  precedence token;
  char symbol;
  int op1, op2;
  int n = 0;

  token = getToken(&symbol, &n);

  while(token != eos) {
    if(token == operand) push(symbol - '0');  // insert operand to stack
    else {
      /* remove two operands, perform operation, and return result to the stack */
      op2 = pop();
      op1 = pop();
      switch(token) {
        case plus: push(op1+op2); break;
        case minus: push(op1-op2); break;
        case times: push(op1*op2); break;
        case divide: push(op1/op2); break;
        case mod: push(op1%op2);
      }
    }
    token = getToken(&symbol, &n);
  }
  return pop();    /* return result */
}

precedence getToken(char *symbol, int *n) {
  *symbol = expr[(*n)++];

  switch(*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '\0': return eos;
    default: return operand;
  }
}

void push(int item) {
  if(top >= MAX_STACK_SIZE - 1) stackFull();
  stack[++top] = item;
  //printf("item %d pushed to the stack.\n", item);
}

int pop() {
  int rv;
  if(top == -1) return stackEmpty();
  rv = stack[top--];
  //printf("item %d popped out of the stack.\n", rv);
  return rv;
}

void stackFull() {
  fprintf(stderr, "stack is full, cannot add element.\n");
  exit(EXIT_FAILURE);
}

int stackEmpty() {
  return -1;
}
