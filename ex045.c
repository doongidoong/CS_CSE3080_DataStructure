#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10000
#define INF 999999999
#define TRUE 1
#define FALSE 0

int numVertices;
int numEdges;
int cost[MAX_VERTICES][MAX_VERTICES];

int v;
int distance[MAX_VERTICES];
int parent[MAX_VERTICES];
int path[MAX_VERTICES];
int found[MAX_VERTICES];

void createGraph();
void shortestPath();
int choose();

void main() {

    int i, j;
    int path_curr, path_count;

    createGraph();
    
    for(i=0; i<numVertices; i++) {
        distance[i] = INF;
        parent[i] = -1;
    }

    v = 0;
    shortestPath();

    for(i=0; i<numVertices; i++) {
        if(distance[i] != INF) {
            printf("SRC: %d, DST: %d, LENGTH: %3d, PATH: %d", v, i, distance[i], v);
            
            /* print path */
            path_curr = i;
            path_count = 0;
            while(parent[path_curr] > -1) {
                path[path_count++] = path_curr;
                path_curr = parent[path_curr];
            }
            for(j=path_count-1; j>=0; j--) {
                printf(" %d", path[j]);
            }
            printf("\n");
        }
        else {
            printf("SRC: %d, DST: %d, LENGTH: ---, PATH: -\n", v, i);
        }
    }
}

void createGraph() {
    int i, j;
    numVertices = 6;
    numEdges = 11;
    
    // cost adjacency matrix
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            cost[i][j] = INF;
        }
    }

    cost[0][1] = 50;
    cost[0][2] = 45;
    cost[0][3] = 10;
    cost[1][3] = 15;
    cost[1][2] = 10;
    cost[2][4] = 30;
    cost[3][0] = 20;
    cost[3][4] = 15;
    cost[4][1] = 20;
    cost[4][2] = 35;
    cost[5][4] = 3;
}

void shortestPath() {
    int i, u, w;
    for(i=0; i<numVertices; i++) {
        found[i] = FALSE;
        distance[i] = cost[v][i];
        if(distance[i] < INF) {
            parent[i] = v;
        }
    }

    found[v] = TRUE;
    distance[v] = 0;
    for(i=0; i<numVertices-2; i++) {
        u = choose();
        if(u == -1) break;
        found[u] = TRUE;
        for(w=0; w<numVertices; w++) {
            if(!found[w] && (u != w)) {
                if(distance[u] + cost[u][w] < distance[w]) {
                    distance[w] = distance[u] + cost[u][w];
                    parent[w] = u;
                }
            }
        }
    }
}

int choose() {
    /* find the smallest distance not yet checked */
    int i, min, minpos;
    min = INF;
    minpos = -1;
    
    for(i=0; i<numVertices; i++) {
        if(distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}