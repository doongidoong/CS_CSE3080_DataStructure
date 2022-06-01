#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 1000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

//define structure for implementing heap (using array)
typedef struct {
  int key;
} element;
element maxHeap[MAX_ELEMENTS];
element minHeap[MAX_ELEMENTS];
element heap[MAX_ELEMENTS];
int n = 0;//엘리먼트 개수

void insert_max_heap(element item, int n);
void insert_min_heap(element item, int n);

element delete_max_heap(int *n);
element delete_min_heap(int *n);


int main(int argc, char *argv[]) {
	FILE *input_fp, *output_fp;
	element item;
	clock_t start, end;
	char command[8];
	int i;
	input_fp = fopen(argv[1], "r");// input 
	output_fp = fopen("hw2_result.txt", "w"); //output
	/*checking input error*/
	if(argc!=2){//받는 인자가 2 개가 아니라면 error 
		fprintf(stderr, "usage: ./hw2 input_filename\n");
		return 1;}
	if (input_fp == NULL){
		fprintf(stderr, "The input file does not exist.\n");
		return 1;
		}
	start = clock();
	while (1) {
		fscanf(input_fp, "%s %d", command, &(item.key));
		if(command[0]=='I') {
			insert_max_heap(item,n);
			insert_min_heap(item,n);
			n++;
		}
		if(command[0]=='A') {
			memcpy(heap, minHeap, sizeof(element) * (n+1));
			int temp =n;
			for(i=0; i<n; i++) {
				item = delete_min_heap(&temp);
				fprintf(output_fp, "%d ", item.key);
			}
			fprintf(output_fp,"\n");
		}
		if(command[0]=='D') {
			memcpy(heap, maxHeap, sizeof(element) * (n+1));
			int temp =n;
			for(i=0; i<n; i++) {
				item = delete_max_heap(&temp);
				fprintf(output_fp, "%d ", item.key);
			}
			fprintf(output_fp,"\n");
		}
		if (feof(input_fp))
			break;
	}
	end = clock();
	printf("output written to hw2_result.txt.\n");
	printf("running time: %lf seconds  \n",(double)(end-start)/CLOCKS_PER_SEC);
	// printf("insert =%d \n",n);
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}

void insert_max_heap(element item, int n) {
  /* insert item into a max heap of current size *n */
  int i;
  if(HEAP_FULL(n)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(n);
  while((i != 1) && (item.key > maxHeap[i/2].key)) {
    maxHeap[i] = maxHeap[i/2];
    i /= 2;
  }
  maxHeap[i] = item; 
}
void insert_min_heap(element item, int n) {
  /* insert item into a max heap of current size *n */
  int i;
  if(HEAP_FULL(n)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(n);
  while((i != 1) && (item.key < minHeap[i/2].key)) {
    minHeap[i] = minHeap[i/2];
    i /= 2;
  }
  minHeap[i] = item; 
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
  temp = heap[(*n)--];
  parent = 1; //시작 parent
  child = 2; 
  while(child <= *n) {
    if((child < *n) && (heap[child].key < heap[child+1].key)) child++; 

    if(temp.key >= heap[child].key) break;

    heap[parent] = heap[child]; 
    parent = child;
    child *= 2;
  }
  heap[parent] = temp;
  return item;
}
element delete_min_heap(int *n) {
  int parent, child;
  element item, temp;
  if(HEAP_EMPTY(*n)) {
    fprintf(stderr, "The heap is empty");
    exit(1);
  }
  item = heap[1]; //지울 아이템
  temp = heap[(*n)--]; //바꿔치기할 아이템을 꺼내놓고, n은 1 줄임
  parent = 1; //시작 parent
  child = 2; 
  while(child <= *n) { //child가 있는 경우만 while
    if((child < *n) && (heap[child].key > heap[child+1].key)) child++;
    if(temp.key <= heap[child].key) break;
    heap[parent] = heap[child]; // child를 parent로 올려주고
    parent = child;//이제 비교할 parent를 child로 
    child *= 2;
  }
  heap[parent] = temp;
  return item;
}
