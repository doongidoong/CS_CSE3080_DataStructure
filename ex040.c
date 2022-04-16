#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
int parent[MAX_SIZE];

int simpleFind(int i) {
    for( ; parent[i] >= 0; i = parent[i])
        ;
    return i;
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

void main() {

    int i, j, n, found;
    printf("Enter number of items (<= %d) ", MAX_SIZE);
    scanf("%d", &n);

    for(i=0; i<n; i++) parent[i] = -1;

    printf("Enter a pair of equivalent items (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);
    
    weightedUnion(i, j);

    while(i >= 0) {
        printf("Enter a pair of equivalent items (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);

        weightedUnion(simpleFind(i), simpleFind(j));
    }

    for(i=0; i<n; i++) {
        found = 0;
        for(j=0; j<n; j++) {
            if(simpleFind(j) == i) {
                printf("%d ", j);
                found = 1;
            }
        }
        if(found > 0) printf("\n");
    }
}