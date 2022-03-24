#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {

  char pat[] = "world"; 
  char str[] = "Hello world I am a student.";
  char *t;

  if(t = strstr(str, pat)) { //없으면 null이므로
    printf("The string returned by strstr is: %s\n", t); //t가 패턴 위치를 가르키므로 
  } else {
    printf("The pattern was not found with strstr.\n");
  }
}
