//============================================================================//
// ex016: finding a pattern inside a string                                   //
//============================================================================//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nfind(char*, char*);

void main() {

  char pat[] = "wor";
  char str[] = "hello world I am a student.";
  int rv;

  rv = nfind(str, pat);
  if(rv == -1) {
    printf("The pattern %s was not found in the string.\n", pat);
  } else {
    printf("The pattern %s was found at position %d in the string.\n", pat, rv);
  }
}

int nfind(char *string, char *pat) {
  /* try implementing this function yourself! */
  int i,j,start =0 ;
  int lasts = strlen(string)-1;
  int lastp = strlen(pat)-1;
  int endmatch = lastp; //첫 endmath는 pat의 길이부터 시작
  for(i=0;endmatch<=lasts;start++,endmatch++){ //i=0, endmatch가 문자열 끝에 도달할 때까지 반복 
    if(string[endmatch]==pat[lastp]) //만약 endmatch가 pat의 마지막과 동일하다면 아래 반복문 실행
      for(j=0,i=start;j<lastp && string[i]==pat[j];i++,j++); // i의 초기값은 start로 잡고 j는 pat의 첫 부분
    //i와 j를 하나씩 올려가면서 문자열과 비교, 만약 다른 게 있다면 for문을 빠져나옴
    if(j==lastp) return start; //만약 for문을 빠져나오지 않고 모두 돌았다면 return start해줌
  }
}


