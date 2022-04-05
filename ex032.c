#include <stdio.h>
#include <stdlib.h>

#define IS_FULL(x) !x
#define IS_EMPTY(x) !x
#define MAX_QUEUES 10

typedef struct {
  int key;
  /* other fields */
} element;

struct queue {
  element item;
  struct queue *link;
};
typedef struct queue *queue_pointer;

queue_pointer front[MAX_QUEUES], rear[MAX_QUEUES];

void addq(queue_pointer *front, queue_pointer *rear, element item);
element deleteq(queue_pointer *front);
void printQueue(queue_pointer front);

void main() {

  int i;
  for(i=0; i<10; i++) {
    element e;
    e.key = i+1;
    addq(&front[0], &rear[0], e);
    printQueue(front[0]);
  }

  for(i=0; i<10; i++) {
    element e;
    e = deleteq(&front[0]);
    printQueue(front[0]);
  }
}

void addq(queue_pointer *front, queue_pointer *rear, element item) {
  /* add an element to the rear of the queue */
  queue_pointer temp = (queue_pointer)malloc(sizeof(struct queue));
  if(IS_FULL(temp)) {
    fprintf(stderr, "the memory is full\n");
    exit(1);
  }
  temp->item = item;
  temp->link = NULL;
  if(*front) 
    (*rear)->link = temp;
  else *front = temp;
  *rear = temp;
}

element deleteq(queue_pointer *front) {
  /* delete an element from the queue */
  queue_pointer temp = *front;
  element item;
  if(IS_EMPTY(*front)) {
    fprintf(stderr, "the queue is empty\n");
    exit(1);
  }
  item = temp->item;
  *front = temp->link;
  free(temp);
  return item;
}

void printQueue(queue_pointer front) {

  queue_pointer temp = front;
  while(temp != NULL) {
    printf("%2d ", temp->item.key);
    temp = temp->link;
  }
  printf("\n");
}



