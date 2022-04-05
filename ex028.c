#include <stdio.h>
#include <stdlib.h>

struct list_node {
  char data;
  struct list_node *link;
};
typedef struct list_node* list_pointer;

list_pointer invert(list_pointer);
void print_list(list_pointer);

void main() {

  /* make four list nodes and connect them to make a list */
  list_pointer head, a, b, c, d, inverted;
  a = (list_pointer)malloc(sizeof(struct list_node));
  b = (list_pointer)malloc(sizeof(struct list_node));
  c = (list_pointer)malloc(sizeof(struct list_node));
  d = (list_pointer)malloc(sizeof(struct list_node));
  a->data = 'A';
  b->data = 'B';
  c->data = 'C';
  d->data = 'D';
  a->link = b;
  b->link = c;
  c->link = d;
  d->link = NULL;
  head = a;

  print_list(head);
  inverted = invert(head);
  print_list(inverted);
}

list_pointer invert(list_pointer lead) {
  /* invert the list pointed by lead */
  list_pointer middle, trail;
  middle = NULL;
  while(lead) {
    trail = middle;
    middle = lead;
    lead = lead->link;
    middle->link = trail;
  }
  return middle;
}

void print_list(list_pointer lead) {
  list_pointer temp = lead;
  while(temp) {
    printf("%c ", temp->data);
    temp = temp->link;
  }
  printf("\n");
}
