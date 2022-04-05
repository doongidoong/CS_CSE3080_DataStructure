#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define COMPARE(x, y) (x < y ? -1: (x > y ? 1 : 0))
#define IS_FULL(x) !x


struct poly_node {
  float coef;
  int expon;
  struct poly_node *link;
};
typedef struct poly_node* poly_pointer;
poly_pointer avail = NULL;

/* function prototypes */
poly_pointer get_node();
void ret_node(poly_pointer);
void cerase(poly_pointer*);
poly_pointer cpadd(poly_pointer, poly_pointer);
void attach(float, int, poly_pointer*);
void print_polynomial(poly_pointer);

void main() {

  poly_pointer a, a_rear, b, b_rear, d;

  a = get_node();
  a->expon = -1;
  a->link = a;
  a_rear = a;
  attach(3, 14, &a_rear);
  attach(2, 8, &a_rear);
  attach(1, 0, &a_rear);

  b = get_node();
  b->expon = -1;
  b->link = b;
  b_rear = b;
  attach(8, 14, &b_rear);
  attach(-3, 10, &b_rear);
  attach(10, 6, &b_rear); 

  print_polynomial(a);
  print_polynomial(b);
  d = cpadd(a, b);
  print_polynomial(d);

  cerase(&a);
  cerase(&b);
  cerase(&d);
}

poly_pointer get_node(void) {
  /* obtain a node for use */
  poly_pointer node;
  if(avail) {
    node = avail;
    avail = avail->link;
  } else {
    node = (poly_pointer)malloc(sizeof(struct poly_node));
    if(IS_FULL(node)) {
      fprintf(stderr, "The memory is full\n");
      exit(1);
    }
  }
}

void ret_node(poly_pointer ptr) {
  /* return a node to the available list */
  ptr->link = avail;
  avail = ptr;
}


void cerase(poly_pointer *ptr) {
  /* erase the circular list ptr */
  poly_pointer temp;
  if(*ptr) {
    temp = (*ptr)->link;
    (*ptr)->link = avail;
    avail = temp;
    *ptr = NULL;
  }
}


poly_pointer cpadd(poly_pointer a, poly_pointer b) {
  /* Polynomials a and b are singly linked circular lists with a head node.
     This function returns a polynomial which is the sum of a and b. */
  poly_pointer starta, d, lastd;
  int sum, done = FALSE;
  starta = a;      /* record start of a */
  a = a->link;     /* skip head node for a and b */
  b = b->link;
  d = get_node();  /* get a head node for sum */
  d->expon = -1;
  lastd = d;

  do {
    switch(COMPARE(a->expon, b->expon)) {
      case -1:    /* a->expon < b->expon */
        attach(b->coef, b->expon, &lastd);
        b = b->link;
        break;
      case 0:     /* a->expon = b->expon */
        if(starta == a) done = TRUE;
        else {
          sum = a->coef + b->coef;
          if(sum) attach(sum, a->expon, &lastd);
          a = a->link;
          b = b->link;
        }
        break;
      case 1:    /* a->expon > b->expon */
        attach(a->coef, a->expon, &lastd);
        a = a->link;
    }
  } while(!done);
  lastd->link = d;
  return d;
}

void attach(float coefficient, int exponent, poly_pointer *ptr) {

  /* Create a new node and attach it to the node pointed to by ptr.
     ptr is updated to point to this new node. */

  poly_pointer temp;
  temp = (poly_pointer)malloc(sizeof(struct poly_node));
  if(IS_FULL(temp)) {
    fprintf(stderr, "The memory is full\n");
    exit(1);
  }
  temp->coef = coefficient;
  temp->expon = exponent;
  temp->link = (*ptr)->link;
  (*ptr)->link = temp;
  *ptr = temp;
}

void print_polynomial(poly_pointer a) {

  poly_pointer temp = a->link;
  if(temp != a) {
    printf("%.1fx^%d", temp->coef, temp->expon);
    temp = temp->link;
  }
  while(temp != a) {
    if(temp->coef >= 0.0) printf("+%.1fx^%d", temp->coef, temp->expon);
    else printf("%.1fx^%d", temp->coef, temp->expon);
    temp = temp->link;
  }
  printf("\n");
}





