#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;
precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;

static int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

void postfix();
precedence getToken(char*, int*);
void push(precedence);
precedence pop();
void stackFull();
precedence stackEmpty();
void printToken(precedence);

void main() {
  
  //sprintf(expr, "6/2-3+4*2");
  sprintf(expr, "a*(b+c)/d");
  printf("infix  : %s\n", expr);
  printf("postfix: ");
  postfix();

}

void postfix() {
 
  char symbol;
  precedence token;
  int n = 0;
  top = 0;
  stack[0] = eos;

  for(token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {

    if(token == operand) printf("%c", symbol);
    else if(token == rparen) {
      while(stack[top] != lparen)
        printToken(pop());
      pop();
    }
    else {
      /* remove and print symbols whose isp is greater than or equal to the current token's icp */
      while(isp[stack[top]] >= icp[token]) printToken(pop());
      push(token);
    }
  }
  while((token = pop()) != eos) printToken(token);
  printf("\n");
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

void printToken(precedence token) {
  switch(token) {
    case lparen: printf("("); break;
    case rparen: printf(")"); break;
    case plus:   printf("+"); break;
    case minus:  printf("-"); break;
    case divide: printf("/"); break;
    case times:  printf("*"); break;
    case mod:    printf("%%"); break;
  }
}

void push(precedence item) {
  if(top >= MAX_STACK_SIZE - 1) stackFull();
  stack[++top] = item;
}

precedence pop() {
  if(top == -1) return stackEmpty();
  return stack[top--];
}

void stackFull() {
  fprintf(stderr, "stack is full, cannot add element.\n");
  exit(EXIT_FAILURE);
}

precedence stackEmpty() {
  fprintf(stderr, "stack is empty, cannot delete element.\n");
  exit(EXIT_FAILURE);
}

