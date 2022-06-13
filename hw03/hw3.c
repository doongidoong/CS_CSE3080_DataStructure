#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 50000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)


//define structure for implementing heap (using array)
typedef struct {
  int node1;
  int node2;
  int key;
} edge;

int parent[10000];
edge heap[MAX_ELEMENTS];
int n = 0;//엘리먼트 개수
void insert_min_heap(edge item, int n);
edge delete_min_heap(int *n);
void weightedUnion(int i, int j);
int collapsingFind(int i);

int main(int argc, char *argv[]) {
	FILE *input_fp, *output_fp;
	edge input_edge;
	clock_t start, end;
	input_fp = fopen(argv[1], "r");// input 
	output_fp = fopen("hw3_result.txt", "w"); //output
	/*checking input error*/
	if(argc!=2){//받는 인자가 2 개가 아니라면 error 
		fprintf(stderr, "usage: ./hw3 input_filename\n");
		return 1;}
	if (input_fp == NULL){
		fprintf(stderr, "The input file does not exist.\n");
		return 1;
		}
	start = clock();
  int vor_num, edge_num;
  fscanf(input_fp, "%d",&vor_num );
  for(int i=0; i<vor_num; i++) parent[i] = -1;
  // printf("%d",vor_num);
  fscanf(input_fp, "%d",&edge_num );
  // printf(" %d\n",edge_num);
  
	while (1) {
		fscanf(input_fp, "%d %d %d", &(input_edge.node1),&(input_edge.node2),&(input_edge.key));
		insert_min_heap(input_edge,n);
    n++;
    if (feof(input_fp))
			break;
	}
 
  int cost=0;
  int parent1,parent2;
  for(int i=0;i<edge_num;i++){
    edge temp = delete_min_heap(&n);
    parent1= collapsingFind(temp.node1);
    parent2 = collapsingFind(temp.node2);
    if(parent1!=parent2) {
        fprintf(output_fp,"%d %d %d\n",temp.node1,temp.node2,temp.key);
        // printf("%d parent = %d, %d parent = %d\n",temp.node1,simpleFind(temp.node1),temp.node2,simpleFind(temp.node2));
        weightedUnion(parent1, parent2);
        cost+=temp.key;
        }
      if(parent[parent1]==-1)break;
    }
  fprintf(output_fp,"%d\n",cost);
  //   for(int i=0;i<vor_num;i++){
  //     printf("%d ",parent[i]);
  // }
  // printf("\n");
	if(parent[collapsingFind(0)]==-1*vor_num){
    fprintf(output_fp,"CONNECTED");
  }
  else fprintf(output_fp,"DISCONNECTED");
  
  end = clock();
	printf("output written to hw3_result.txt.\n");
	printf("running time: %lf seconds  \n",(double)(end-start)/CLOCKS_PER_SEC);
	// printf("insert =%d \n",n);
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}
int collapsingFind(int i) {
  int root, trail, lead;
  for(root = i; parent[root] >= 0; root = parent[root])
  ;
  for(trail = i; trail != root; trail = lead) {
  lead = parent[trail];
  parent[trail] = root;
  }
  return root;
}

void insert_min_heap(edge item, int n) {
  /* insert item into a max heap of current size *n */
  int i;
  if(HEAP_FULL(n)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(n);
  while((i != 1) && (item.key < heap[i/2].key)) {
    heap[i] = heap[i/2];
    i /= 2;
  }
  heap[i] = item; 
}


edge delete_min_heap(int *n) {
  int parent, child;
  edge item, temp;
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
void weightedUnion(int i, int j) {
    int temp = parent[i] + parent[j];
    if(parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }
}

// int simpleFind(int i) {
//     for( ; parent[i] >= 0; i = parent[i])
//         ;
//     return i;
// }
