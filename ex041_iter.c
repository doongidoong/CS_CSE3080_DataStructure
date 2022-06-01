#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define INVALID_KEY -1
#define MAX_STACKS_SIZE 20
#define IS_FULL(x) !x
#define IS_EMPTY(x) !x


struct node {
    int vertex;
    struct node *link;
};
typedef struct node* nodePointer;

struct stack{
  int item;
  struct stack *link;
  /* other fields if necessary */
};

typedef struct stack * stack_pointer;
stack_pointer top;

void push(stack_pointer *top,int item){
  stack_pointer temp = *top;
  temp->item = item;
  temp->link = *top;
  *top = temp;
}
int pop(stack_pointer *top){
  stack_pointer temp = *top;
  int item;
  if(*top==NULL){
    printf("empty\n");
    exit(0);
  }
  item =temp->item;
  *top =temp->link;
  free(temp);
  return item;
}
nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];
void dfs(int v){
    nodePointer w;
    int u;
    push(&top,v);
    while(top){
        u =pop(&top);
        if(!visited[u]){
            printf("%5d",u);
            visited[u]=1;
            for(w=graph[u];w;w=w->link){
                if(!visited[w->vertex]){
                    push(&top,w->vertex);
                }
            }
        }
    }
}

void main() {

    nodePointer prev;
    nodePointer np;
    //0과 인접한 노드들을 먼저 만들어 줌
    /* adjacency list for vertex 0 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 1; np->link = NULL; graph[0] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 2; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 1 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 0; np->link = NULL; graph[1] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 3; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 4; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 2 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 0; np->link = NULL; graph[2] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 5; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 6; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 3 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 1; np->link = NULL; graph[3] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 4 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 1; np->link = NULL; graph[4] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 5 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 2; np->link = NULL; graph[5] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 6 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 2; np->link = NULL; graph[6] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 7; np->link = NULL; prev->link = np;

    /* adjacency list for vertex 7 */
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 3; np->link = NULL; graph[7] = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 4; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 5; np->link = NULL; prev->link = np; prev = np;
    np = (nodePointer)malloc(sizeof(struct node)); np->vertex = 6; np->link = NULL; prev->link = np;

    for(int i=0; i<8; i++) visited[i] = 0;
    dfs(0);
    printf("\n");
}

