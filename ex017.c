//============================================================================//
// ex017.c: Knuth-Morris-Pratt Algorithm for Pattern Matching                 //
//============================================================================//
/*fail의 가장 중요한 점은 fail에 패턴이 어디까지 겹치는 지 저장하는 것이다
    예를 들어 A,B,C,A,B가 있을 경우 네 번째 패턴인 'A'에 해당하는 Fail[3]에 0('A')을 넣고  Fail[4]는 1('AB')를 넣는다.
    그렇다면 만약 ABCABCAB는 어떻게 되는가? -1,-1,-1,0,1,2,3,4가 될 것이다.
    이번에는 다른 예인 ABCABDF는? -1,-1,-1,0,1,-1,-1이 될 것이다.
    이 과정이 필요한 이유는 나중에 문자열을 비교할 때, 만약 A,B가 있으면 그 값부터 비교할 수 있게 하기 위해서다.
    
    만약 ABCABABCABDF와 ABCABDF를 비교한다고 가정하자. 이럴 경우 fail은 앞서 보았듯 [-1,-1,-1,0,1,-1,-1]이다. 
    이를 비교하다보면 먼저 ABCAB'A'에서 매칭이 되지 않는다. 
    그런데 이 경우 처음부터 비교하는 것이 아니라 매칭되지 않은 pattern 직전의 Fail을 부른다. 
    그렇다면 이전까지 잘 매칭된 ABCA'B'에 해당하는 fail[4]이 1이기 때문에 pattern이 A'B'CA'B'까지 반복되는 것을 알 수 있다. 
    그러므로 다음 비교 시 비교하는 pattern의 pattern[2], 즉 3번째부터 비교하면 된다.      
    하지만 이 경우 ABC(AB'A')는 AB'C'와 다시 일치하지 않게 된다. 
    그럼 다시 'B'의 Fail을 불러오는데 이때 B는 Fail[1]이므로 -1이 된다. 즉, 이제부터 pattern은 처음부터 비교하게 된다.
    그러므로 (ABCAB)'A'BCABDF와 'A'BCABDF를 비교하게 되고 이제 매칭되지 않는 부분이 없으니 매칭되는 부분을 찾게 된다.
    */
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 100
#define MAX_PATTERN_SIZE 100

int pmatch(char*, char*);
void fail(char*);

int failure[MAX_PATTERN_SIZE];
char string[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];

void main() {

  int rv, i;
  strcpy(string, "ababcabcabababdabaabaabacabaababaaabaabaacaaba");
  strcpy(pat, "abaababaaaba");
  fail(pat);
  for(i=0; i<strlen(pat); i++) {
    printf("%d ", failure[i]);
  }
  printf("\n"); 
  rv = pmatch(string, pat);
  printf("rv: %d\n", rv);
}

void fail(char *pat) {

  /* compute pattern's failure function */
  int i, j, n = strlen(pat);
  failure[0] = -1; // 첫 값은 -1
  for(j=1; j<n; j++) { 
    i = failure[j-1]; // 일단 처음에는 겹치는 게 없으므로 -1 
    while((pat[j] != pat[i+1]) && (i >= 0)) i = failure[i];
    if(pat[j] == pat[i+1]) failure[j] = i+1;  
    else failure[j] = -1;
  }
}

int pmatch(char *string, char *pat) {

  /* Knuth-Morris-Pratt string matching algorithm */
  int i=0, j=0;
  int lens = strlen(string);
  int lenp = strlen(pat);
  while(i < lens && j < lenp) {
    if(string[i] == pat[j]) { i++; j++; }//일치할 경우 i와 j를 하나씩  더해간다.
    else if(j == 0) i++; //만약 일치않았는데 j가 0일 경우 그냥 i만(string 비교위치) 옮겨간다.
    else j = failure[j-1] + 1;//일치하지 않았을 경우 j를(pattern 비교위치) 지금까지 일치했던 부분과 반복되는 부분까지 옮겨준다.
  }
  return ((j==lenp) ? (i-lenp) : -1);
}

