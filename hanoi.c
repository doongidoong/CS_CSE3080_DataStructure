#include <stdio.h>
#include <stdlib.h>

int move=0;

void hanoi(int n,char a,char b,char c){
    if(n==1){
        printf("%c to %c \n",a,c);
        move++;
        return;
    }   
    hanoi(n-1,a,c,b);
    printf("%c to %c \n",a,c);
    move++;
    hanoi(n-1,b,a,c);
}
void main() {

  int n=3;
  hanoi(n,'a','b','c');
  printf("**** %d ***",move);
}

