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

void createGraph();
void createGraph2();
void bellmanFord();

void main() {

    int i, j;
    int path_curr, path_count;

    createGraph2();
    
    for(i=0; i<numVertices; i++) {
        distance[i] = INF;
    }

    v = 0;
    bellmanFord();

    for(i=0; i<numVertices; i++) {
        if(distance[i] != INF) {
            printf("SRC: %d, DST: %d, LENGTH: %3d\n", v, i, distance[i]);
        }
        else {
            printf("SRC: %d, DST: %d, LENGTH: ---\n", v, i);
        }
    }
}

void bellmanFord() {
    int i, j, k;
    for(i=0; i<numVertices; i++) {
        distance[i] = cost[v][i];
    }
    distance[v] = 0;
    for(k=2; k<numVertices; k++) {
        for(i=0; i<numVertices; i++) {
            for(j=0; j<numVertices; j++) {
                if(cost[i][j] == INF) continue;
                // relaxation
                if(distance[j] > distance[i] + cost[i][j]) 
                    distance[j] = distance[i] + cost[i][j];
            }
        }
    }
}

void createGraph() {
    int i, j;
    numVertices = 7;
    numEdges = 10;
    
    // cost adjacency matrix
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            cost[i][j] = INF;
        }
    }

    cost[0][1] = 6;
    cost[0][2] = 5;
    cost[0][3] = 5;
    cost[1][4] = -1;
    cost[2][1] = -2;
    cost[2][4] = 1;
    cost[3][2] = -2;
    cost[3][5] = -1;
    cost[4][6] = 3;
    cost[5][6] = 3;
}

void createGraph2() {
    int i, j;
    numVertices = 4;
    numEdges = 4;
    
    // cost adjacency matrix
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            cost[i][j] = INF;
        }
    }

    cost[0][1] = 3;
    cost[0][3] = 5;
    cost[2][1] = -6;
    cost[3][2] = 2;
}
