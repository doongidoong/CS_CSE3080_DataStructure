#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define MIN2(x,y) ((x) < (y) ? (x) : (y))

struct node {
    int vertex;
    struct node *link;
};
typedef struct node* nodePointer;

nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];
int n;

void dfs(int v) {
  /* depth first search of a graph beginning at v */
  nodePointer w;
  visited[v] = 1;  // visited[] is a global variable
//   printf("%5d", v);
  for(w = graph[v]; w; w = w->link)
    if(!visited[w->vertex])
      dfs(w->vertex);
}

void createGraph() {
    nodePointer prev;
    nodePointer np;

    /* adjacency list for vertex 0 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 1;
    np->link = NULL;
    graph[0] = np;

    /* adjacency list for vertex 1 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 0;
    np->link = NULL;
    graph[1] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 2;
    np->link = NULL;   
    prev->link = np;
    prev = np;

    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 3;
    np->link = NULL;   
    prev->link = np;

    /* adjacency list for vertex 2 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 1;
    np->link = NULL;
    graph[2] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 4;
    np->link = NULL;   
    prev->link = np;

    /* adjacency list for vertex 3 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 4;
    np->link = NULL;
    graph[3] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 1;
    np->link = NULL;   
    prev->link = np;
    prev = np;

    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 5;
    np->link = NULL;   
    prev->link = np;

    /* adjacency list for vertex 4 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 2;
    np->link = NULL;
    graph[4] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 3;
    np->link = NULL;   
    prev->link = np;
    
    /* adjacency list for vertex 5 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 3;
    np->link = NULL;
    graph[5] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 6;
    np->link = NULL;   
    prev->link = np;
    prev = np;

    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 7;
    np->link = NULL;   
    prev->link = np;

    /* adjacency list for vertex 6 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 5;
    np->link = NULL;
    graph[6] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 7;
    np->link = NULL;   
    prev->link = np;
    
    /* adjacency list for vertex 7 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 5;
    np->link = NULL;
    graph[7] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 6;
    np->link = NULL;   
    prev->link = np;
    prev = np;

    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 9;
    np->link = NULL;   
    prev->link = np;
    prev = np;

    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 8;
    np->link = NULL;   
    prev->link = np;

    /* adjacency list for vertex 8 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 7;
    np->link = NULL;
    graph[8] = np;

    /* adjacency list for vertex 9 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 7;
    np->link = NULL;
    graph[9] = np;

    n=10;

}

void main(){
    int i,k;
    createGraph();
    for(k=0;k<n;k++){
        for(i=0;i<n;i++) visited[i]=0;//visted 초기화
        visited[k]=1;

        if(k==0) dfs(1);//dfs는 어디서부터 시작해도 됨 그러나 제거한 node면 안됨 따라서 k=0일 때는 dfs(1)
        else dfs(0); //나머지는 dfs0
        for(i=0; i<n;i++){
            if(visited[i]==0){
                printf("%d is an articulation pount \n",k);
                break;  
            }
        }
    }

}