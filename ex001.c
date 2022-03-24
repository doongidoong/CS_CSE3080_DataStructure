#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 1001

int main(int argc, char *argv[]) {
  
  int data[MAX_NUMBERS];
  int sorted_data[MAX_NUMBERS];
  int cnt = 0;
  int buf;
  int i;
  
  while(1) {
    printf("Enter a number: ");
    scanf("%d", &buf);

    data[cnt] = buf;
    for(i=cnt-1; i>=0; i--) {
      if(sorted_data[i] > buf) {
        sorted_data[i+1] = sorted_data[i];
      }
      else {
        sorted_data[i+1] = buf;
        break;
      }
    }
    if(i < 0) {
      sorted_data[0] = buf;
    }

    cnt++;

    printf("unsorted: ");
    for(i=0; i<cnt; i++) {
      printf("%d ", data[i]);
    }
    printf("\n");
    printf("sorted: ");
    for(i=0; i<cnt; i++) {
      printf("%d ", sorted_data[i]);
    }
    printf("\n");
  }

  return 0;
}
