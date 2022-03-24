#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void strnins(char*, char*, int);

void main() {

  char s[MAX_SIZE] = "amobile";
  char t[MAX_SIZE] = "uto";
  strnins(s, t, 1);
  printf("%s\n", s);
}

void strnins(char *s, char *t, int i) {

  /* complete this function! */
  char temp[MAX_SIZE]={'\0'};
  //char temp[MAX_SIZE]={'\0'}; 아래 예시에서 이렇게 \0으로 초기화해주면 됨. 혹은 뒤에 \0을 붙여주면됨 
  if(i<0 || i> strlen(s)){ //위치가 0보다 작을 수 없고 s의 길이보다 클 수 없음
    fprintf(stderr,"position out of bounds.\n"); //파일 끝내기 에러
    exit(1);
  }
  if(!strlen(s)) strcpy(s,t); //s의 길이가 0일 경우 그냥 t를 복사
  else if(strlen(t)){//만약 붙여되는 t의 길이가 0이 아닐때만 
    strncpy(temp, s, i); //몇 바이트만 카피하자
    strcat(temp,t);//이제 t를 붙여줌
    strcat(temp,(s+i)); //앞서 붙인 부분 이후로 temp에 s의 남은 값을 붙여줌
    strcpy(s,temp);//이제 s를 붙임
    /*
    깨지는 이유는 strncpy는 뒤에 널문자를 넣어주지않기때문에
    */
  }
}
