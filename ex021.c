#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
#define INVALID_KEY -1

typedef struct {
  int key;
  /* other fields if necessary */
} element;

element queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;
int size= 0;
void addq(element);
element deleteq();
void queueFull();
element queueEmpty();

void main() {

  int i;
  element e;

  for(i = 0; i < 10; i++) {
    e.key = i;
    addq(e);
    printf("key %2d inserted into the queue. (front: %2d rear: %2d size: %2d)\n", e.key, front, rear,size);
  }

  for(i = 0; i < 11; i++) {
    e = deleteq();
    printf("key %2d  deleted from the queue. (front: %2d rear: %2d size: %2d)\n", e.key, front, rear,size);
  }

  for(i = 8; i < 16; i++) {
    e.key = i;
    addq(e);
    printf("key %2d inserted into the queue. (front: %2d rear: %2d size: %2d)\n", e.key, front, rear,size);
  }

  for(i = 8; i < 16; i++) {
    e = deleteq();
    printf("key %2d  deleted from the queue. (front: %2d rear: %2d size: %2d)\n", e.key, front, rear,size);
  }
}

void addq(element item) {
  /* add an item to the queue */
  rear = (rear + 1) % MAX_QUEUE_SIZE;
  if(size==MAX_QUEUE_SIZE) queueFull();
  // if(front == rear)queueFull();
  size++;
  queue[rear] = item;
}

element deleteq() {
  /* remove element at the front of the queue */
  if(size==0)
    return queueEmpty();
  front = (front + 1) % MAX_QUEUE_SIZE;
  size--;
  return queue[front];
}

void queueFull() {
  fprintf(stderr, "no more space in the queue\n");
  exit(1);
}

element queueEmpty() {
  element e;
  e.key = INVALID_KEY;
  return e;
}
