#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int key;
} element;

struct node {
  struct node* llink;
  element item;
  struct node* rlink;
};
typedef struct node* node_pointer;

void dinsert(node_pointer, node_pointer);
void ddelete(node_pointer, node_pointer);
void dprint(node_pointer);
void dprintreverse(node_pointer);

void main() {

  node_pointer head, curr, newnode, delnode;
  int i;
  
  /* create a head node for the linked list */
  head = (node_pointer)malloc(sizeof(struct node));
  head->item.key = -1;
  head->rlink = head;
  head->llink = head;

  curr = head;
  for(i=0; i<10; i++) {
    newnode = (node_pointer)malloc(sizeof(struct node));
    newnode->item.key = i+1;
    newnode->rlink = NULL;
    newnode->llink = NULL;
    dinsert(curr, newnode);
    curr = newnode;  
    dprintreverse(head);
  }

  curr = head->rlink;
  while(curr != head) {
    delnode = curr;
    curr = curr->rlink;
    ddelete(head, delnode);
    dprintreverse(head);
  }
}

void dinsert(node_pointer node, node_pointer newnode) {
  /* insert newnode to the right of the node */
  newnode->llink = node;
  newnode->rlink = node->rlink;
  node->rlink->llink = newnode;
  node->rlink = newnode;
}

void ddelete(node_pointer node, node_pointer deleted) {
  /* delete from the doubly linked list */
  if(node == deleted)
    printf("Deletion of head node not permitted.\n");
  else {
    deleted->llink->rlink = deleted->rlink;
    deleted->rlink->llink = deleted->llink;
    free(deleted);
  }
}

void dprint(node_pointer head) {
  node_pointer curr = head->rlink;
  while(curr != head) {
    printf("%2d ", curr->item.key);
    curr = curr->rlink;
  }
  printf("\n");
}

void dprintreverse(node_pointer head) {
  node_pointer curr = head->llink;
  while(curr != head) {
    printf("%2d ", curr->item.key);
    curr = curr->llink;
  }
  printf("\n");
}


