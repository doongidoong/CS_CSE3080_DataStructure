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
int parent[MAX_VERTICES];
int dfn[MAX_VERTICES];
int low[MAX_VERTICES];
int num;
int n;

void createGraph(void);
void createGraph2(void);
void init(void);
void dfnlow(int u, int v);
int checkAp(int u);

void main() {
    int i;
    createGraph();
    init();
    dfnlow(3, -1);
    for(i=0; i<n; i++) {
        printf("dfn[%d]: %2d  low[%d]: %2d  parent[%d]: %2d  ", i, dfn[i], i, low[i], i, parent[i]);
        if(checkAp(i)) printf("ARTICULATION POINT");
        printf("\n");
    }
}

void init() {
    int i;
    for(i=0; i<n; i++) {
        dfn[i] = low[i] = parent[i] = -1;
    }
    num = 0;
}

void dfnlow(int u, int v) {
    nodePointer ptr;
    int w;
    dfn[u] = low[u] = num++;
    for(ptr = graph[u]; ptr; ptr = ptr->link) {
        w = ptr->vertex;
        if(dfn[w] < 0) {
            parent[w] = u;
            dfnlow(w, u);
            low[u] = MIN2(low[u], low[w]);
        }
        else if(w != v) {
            low[u] = MIN2(low[u], dfn[w]);
        }
    }
}

int checkAp(int u) {
   
    if(dfn[u] == 0) {
        /* if u is root, then check whether it has more than one child nodes. */
        int nChild = 0;
        nodePointer ptr = graph[u];
        while(ptr) {
            if(parent[ptr->vertex] == u) nChild++;
            ptr = ptr->link;    
        }
        if(nChild > 1) return TRUE;
        else return FALSE;
    }
    else {
        /* if u is non-root, then check whether it has a chlid w, where low[w] >= dfn[u]. */
        nodePointer ptr = graph[u];
        while(ptr) {
            if(dfn[ptr->vertex] > dfn[u]) {
                if(parent[ptr->vertex] == u)
                    /* ptr->vertex is a child of u */
                    if(low[ptr->vertex] >= dfn[u]) return TRUE;
            }
            ptr = ptr->link;
        }
        return FALSE;
    }
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

    n = 10;
}

void createGraph2() {
    nodePointer prev;
    nodePointer np;

    /* adjacency list for vertex 0 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 1;
    np->link = NULL;
    graph[0] = np;
    prev = np;

    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 3;
    np->link = NULL;   
    prev->link = np;
    
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
  
    /* adjacency list for vertex 2 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 1;
    np->link = NULL;
    graph[2] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 3;
    np->link = NULL;   
    prev->link = np;

    /* adjacency list for vertex 3 */
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 0;
    np->link = NULL;
    graph[3] = np;
    prev = np;
    
    np = (nodePointer)malloc(sizeof(struct node));
    np->vertex = 2;
    np->link = NULL;   
    prev->link = np;

    n = 4;
}
