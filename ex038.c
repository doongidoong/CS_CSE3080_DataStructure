#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

//define structure for implementing heap (using array)
typedef struct {
  int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;//엘리먼트 개수

void insert_max_heap(element item, int *n);
element delete_max_heap(int *n);

void main() {

  int i, rn;
  element item;

  srand(time(NULL));
 
  printf("INSERTING: ");
  for(i=0; i<10; i++) {
    rn = rand() % 100 + 1;
    printf("%3d ", rn);
    item.key = rn;
    insert_max_heap(item, &n);
  }
  printf("\n\n");

  printf("DELETING:  ");
  for(i=0; i<10; i++) {
    item = delete_max_heap(&n);
    printf("%3d ", item.key);
  }
  printf("\n");
}

void insert_max_heap(element item, int *n) {
  /* insert item into a max heap of current size *n */
  int i;
  if(HEAP_FULL(*n)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(*n);
  while((i != 1) && (item.key > heap[i/2].key)) {
    heap[i] = heap[i/2];//자식이 부모보다 크면 일단 부모를 자식의 위치에 넣어줌
    i /= 2;
  }
  heap[i] = item; //더 이상 자식이 크지 않을 경우, 그 위치에 item을 넣어줌
}

element delete_max_heap(int *n) {
  /* delete element with the highest key from the heap */
  int parent, child;
  element item, temp;
  if(HEAP_EMPTY(*n)) {
    fprintf(stderr, "The heap is empty");
    exit(1);
  }
  /* save value of the element with the largest key */
  item = heap[1]; //지울 아이템
  /* use the last element in the heap to adjust heap */
  temp = heap[(*n)--]; //바꿔치기할 아이템을 꺼내놓고, n은 1 줄임
  parent = 1; //시작 parent
  child = 2; 
  while(child <= *n) { //child가 있는 경우만 while
    /* find the larger child of the current parent */
    if((child < *n) && (heap[child].key < heap[child+1].key)) child++; //child+1도 존재한다면 둘 중에 큰 값을 가르키도록 함. 
    // child는 2씩 증가하는데 이 child보다 n이 더 크다면, child는 마지막이 아님. 따라서 child+1도 존재함.

    if(temp.key >= heap[child].key) break;//temp가 더 크면 break
    /* move to the next lower level */
    heap[parent] = heap[child]; // child를 parent로 올려주고
    parent = child;//이제 비교할 parent를 child로 
    child *= 2;
  }
  heap[parent] = temp;
  return item;
}

