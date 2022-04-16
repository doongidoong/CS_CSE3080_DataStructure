#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
#define TRUE 1
#define FALSE 0

typedef enum {NOT, AND, OR, T, F} logical;
struct node {
  struct node *leftChild;
  logical data;
  char variable;
  short int value;
  struct node *rightChild;
};
typedef struct node* treePointer;

typedef enum {lparen, rparen, and, or, not, eos, operand} precedence;
precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char exprpost[MAX_EXPR_SIZE];
int iter = 0;
int top = -1;
treePointer tstack[MAX_STACK_SIZE];
int ttop = -1;
treePointer binaryTree = NULL;

static int isp[] = {0, 19, 5, 4, 15, 0};
static int icp[] = {20, 19, 5, 4, 15, 0};

void postfix();
precedence getToken(char*, int*);
void push(precedence);
precedence pop();
void stackFull();
precedence stackEmpty();
void printToken(precedence);
void generateTree();
void postOrderEval(treePointer);
void tpush(treePointer);
treePointer tpop();
void postorder(treePointer);
void assignTF(treePointer, short int a, short int b, short int c);

void main() {

  int i;
  sprintf(expr, "(a&~b)|(~a&c)|~c");
  printf("infix  : %s\n", expr);
  printf("postfix: ");
  postfix();
  printf("\n");
  generateTree();

  for(i=0; i<8; i++) {
    assignTF(binaryTree, (i/4)%2, (i/2)%2, i%2);
    printf(" %d %d %d ==> ", (i/4)%2, (i/2)%2, i%2);
    postOrderEval(binaryTree);
    if(binaryTree->value == TRUE) {
      printf("result: TRUE\n");
    } else {
      printf("result: FALSE\n");
    }
  }
}

void assignTF(treePointer ptr, short int a, short int b, short int c) {
  if(ptr) {
    assignTF(ptr->leftChild, a, b, c);
    assignTF(ptr->rightChild, a, b, c);
    if(ptr->variable == 'a') {
      if(a == TRUE) ptr->data = T;
      else ptr->data = F;
    }
    else if(ptr->variable == 'b') {
      if(b == TRUE) ptr->data = T;
      else ptr->data = F;
    }
    else if(ptr->variable == 'c') {
      if(c == TRUE) ptr->data = T;
      else ptr->data = F;
    }
  }
}

void postfix() {

  char symbol;
  precedence token;
  int n = 0;
  top = 0;
  stack[0] = eos;

  for(token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {

    if(token == operand) {
      printf("%c", symbol);
      exprpost[iter++] = symbol;
    }
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
  exprpost[iter++] = '\0';
}

precedence getToken(char *symbol, int *n) {
  *symbol = expr[(*n)++];

  switch(*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '&': return and;
    case '|': return or;
    case '~': return not;
    case '\0': return eos;
    default: return operand;
  }
}

void printToken(precedence token) {
  switch(token) {
    case lparen: printf("("); exprpost[iter++] = '('; break;
    case rparen: printf(")"); exprpost[iter++] = ')'; break;
    case and:    printf("&"); exprpost[iter++] = '&'; break;
    case or:     printf("|"); exprpost[iter++] = '|'; break;
    case not:    printf("~"); exprpost[iter++] = '~'; break;
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

void tpush(treePointer item) {
  tstack[++ttop] = item;
}

treePointer tpop() {
  return tstack[ttop--];
}

void stackFull() {
  fprintf(stderr, "stack is full, cannot add element.\n");
  exit(EXIT_FAILURE);
}

precedence stackEmpty() {
  fprintf(stderr, "stack is empty, cannot delete element.\n");
  exit(EXIT_FAILURE);
}

void generateTree() {

  int iter = 0;
  treePointer ptr, lptr, rptr; 

  while(exprpost[iter] != '\0') {

    char tok = exprpost[iter];
    //printf("current token: %c\n", tok);
    ptr = (treePointer)malloc(sizeof(struct node));

    if(tok == '&') {
      rptr = tpop();
      lptr = tpop();

      ptr->variable = tok;
      ptr->data = AND;
      ptr->value = FALSE;
      ptr->leftChild = lptr;
      ptr->rightChild = rptr;

      tpush(ptr);
    } 
    else if(tok == '|') {
      rptr = tpop();
      lptr = tpop();

      ptr->variable = tok;
      ptr->data = OR;
      ptr->value = FALSE;
      ptr->leftChild = lptr;
      ptr->rightChild = rptr;

      tpush(ptr);
    } 
    else if(tok == '~') {
      rptr = tpop();
      
      ptr->variable = tok;
      ptr->data = NOT;
      ptr->value = FALSE;
      ptr->leftChild = NULL;
      ptr->rightChild = rptr;

      tpush(ptr);
    }
    else {
      ptr->variable = tok;
      ptr->data = F;
      ptr->value = FALSE;
      ptr->leftChild = NULL;
      ptr->rightChild = NULL;
 
      tpush(ptr);
    }

    iter++;
  }

  binaryTree = tpop();
}

void postorder(treePointer ptr) {
  if(ptr) {
    postorder(ptr->leftChild);
    postorder(ptr->rightChild);
    printf("%c ", ptr->variable);
  }
}

void postOrderEval(treePointer node) {
  char tok;
  if(node) {
    postOrderEval(node->leftChild);
    postOrderEval(node->rightChild);
    switch(node->data) {
      case NOT:
        node->value = !node->rightChild->value;
        break;
      case AND:
        node->value = node->rightChild->value && node->leftChild->value;
        break;
      case OR:
        node->value = node->rightChild->value || node->leftChild->value;
        break;
      case T:
        node->value = TRUE;
        break;
      case F:
        node->value = FALSE;
    }
  }
}
  
