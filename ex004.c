#include <stdio.h>
#include <stdlib.h>

void main() {
  int i, n, m, *data;
  printf("How many integers do you want to generate? ");
  scanf("%d", &n);
  data = malloc(n*sizeof(int));
  printf("memory allocated at %p\n", data);
  for(i=0; i<n; i++) 
    data[i] = rand()%100;
  printf("How many integers do you want to generate additionally? ");
  scanf("%d", &m);
  data = realloc(data, (n+m)*sizeof(int));
  printf("memory reallocated at %p\n", data);
  for(i; i<n+m; i++) 
    data[i] = rand()%100;
  for(i=0; i<n+m; i++) 
    printf("%3d: %8d\n", i+1, data[i]);
  free(data);
}
