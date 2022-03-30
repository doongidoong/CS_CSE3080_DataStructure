#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
#define INVALID_KEY -1

typedef struct {
  int key;
  /* other fields if necessary */ 
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void addq(element);
element deleteq();
void queueFull();
element queueEmpty();

void main() {

  int i;
  element e;

  for(i = 0; i < 8; i++) {
    e.key = i;
    addq(e);
    printf("key %2d inserted into the queue. (front: %2d rear: %2d)\n", e.key, front, rear);
  }

  for(i = 0; i < 8; i++) {
    e = deleteq();
    printf("key %2d  deleted from the queue. (front: %2d rear: %2d)\n", e.key, front, rear);
  }


  for(i = 8; i < 16; i++) {
    e.key = i;
    addq(e);
    printf("key %2d inserted into the queue. (front: %2d rear: %2d)\n", e.key, front, rear);
  }

  for(i = 8; i < 16; i++) {
    e = deleteq();
    printf("key %2d  deleted from the queue. (front: %2d rear: %2d)\n", e.key, front, rear);
  }

}

// O(MAX_QUEUE_SIZE)
void addq(element item) {
  /* add an item to the queue */
  if(rear == MAX_QUEUE_SIZE-1)
    queueFull();
  queue[++rear] = item;
}

// O(1)
element deleteq() {
  /* remove element at the front of the queue */
  if(front == rear)
    return queueEmpty();
  return queue[++front];
}

void queueFull() {

    //fprintf(stderr, "no more space in the queue\n");
    //exit(1);

  
  int i, offset;

  if(front == -1) { //rear가 마지막 front가 -1 진짜 Full
    fprintf(stderr, "no more space in the queue\n");
    exit(1);
  }

  offset = front + 1; //몇 칸 이동할까

  for(i=front+1; i<MAX_QUEUE_SIZE; i++) { //front가 0이면 앞에 한칸있다는말, 따라서 1부터 시작
    queue[i-offset] = queue[i]; 
  } 

  front = front - offset;
  rear = rear - offset;

  printf(" ==== queue reorganized. (front: %2d rear: %2d) ====\n", front, rear);
  
}

element queueEmpty() {
  element e;
  e.key = INVALID_KEY;
  return e;
}
