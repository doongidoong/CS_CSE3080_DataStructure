#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10000
#define INF 999999999
#define TRUE 1
#define FALSE 0

int numVertices;
int numEdges;
int cost[MAX_VERTICES][MAX_VERTICES];

int distance[MAX_VERTICES][MAX_VERTICES];

void createGraph();
void floydWarshall();

void main() {

    int i, j;

    createGraph();
    
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            distance[i][j] = INF;
        }
    }

    floydWarshall();

    /*
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            if(distance[i][j] != INF) {
                printf("SRC: %d, DST: %d, LENGTH: %3d\n", i, j, distance[i][j]);
            }
            else {
                printf("SRC: %d, DST: %d, LENGTH: ---\n", i, j);
            }
        }
        printf("\n");
    }
    */
}

void floydWarshall() {
    int i, j, k;
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            if(i == j) distance[i][j] = 0;
            else distance[i][j] = cost[i][j];
        }
    }
    for(k=0; k<numVertices; k++) {
        for(i=0; i<numVertices; i++) {
            for(j=0; j<numVertices; j++) {
                if(distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }

        printf("A%d\n", k);
        printf("      0  1  2  3\n");
        for(i=0; i<numVertices; i++) {
            printf("[%2d] ", i);
            for(j=0; j<numVertices; j++) {
                if(distance[i][j] == INF) {
                    printf(" - ");
                }
                else {
                    printf("%2d ", distance[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

void createGraph() {
    int i, j;
    numVertices = 4;
    numEdges = 7;
    
    // cost adjacency matrix
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            cost[i][j] = INF;
        }
    }

    cost[0][1] = 3;
    cost[0][3] = 7;
    cost[1][0] = 8;
    cost[1][2] = 2;
    cost[2][0] = 5;
    cost[2][3] = 1;
    cost[3][0] = 2;
}

