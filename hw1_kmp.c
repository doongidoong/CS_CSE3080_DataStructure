//============================================================================//
// ex017.c: Knuth-Morris-Pratt Algorithm for Pattern Matching                 //
//============================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_SIZE 10000000
#define MAX_PATTERN_SIZE 3000

int pmatch(char*, char*);
void fail(char*);

int failure[MAX_PATTERN_SIZE];
char string[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int arr[MAX_STRING_SIZE]; 
int main() {

  int rv, i;
  FILE* fp = fopen("string.txt", "r");
  if (fp == NULL) {
      printf("the string file does not exist.");
      return 1;
  }
  fgets(string, 10000000, fp);
  FILE* fp2 = fopen("pattern.txt", "r");
  if (fp2 == NULL) {
      printf("the pattern file does not exist.");
      return 1;
  }
  fgets(pat, 3000, fp2);
  fail(pat);
  // for(i=0; i<strlen(pat); i++) {
  //   printf("%d ", failure[i]);
  // }
  double start_time = (double)clock();
  printf("%lf ",(double)start_time);
  rv = pmatch(string, pat);
  double end_time = (double)clock();
  printf("%lf\n",(double)end_time);
  FILE *fp_w= fopen("result_kmp.txt","w");
  if(rv == 0) {
    fprintf(fp_w,"The pattern %s was not found in the string.\n", pat);
  } else {
    fprintf(fp_w, "%d \n",rv);
    for(int i=0;i<rv;i++) fprintf(fp_w,"%d ",arr[i]);
  }
  fclose(fp);
  fclose(fp2);
  fclose(fp_w);
  return 0;
}

void fail(char *pat) {
  /* compute pattern's failure function */
  int i, j, n = strlen(pat);
  failure[0] = -1;
  for(j=1; j<n; j++) {
    i = failure[j-1];
    while((pat[j] != pat[i+1]) && (i >= 0)) i = failure[i];
    if(pat[j] == pat[i+1]) failure[j] = i+1;
    else failure[j] = -1;
  }
}
int pmatch(char *string, char *pat) {
  /* Knuth-Morris-Pratt string matching algorithm */
  int i=0, j=0;
  int cnt=0;
  int lens = strlen(string);
  int lenp = strlen(pat);
  while(i <= lens) {
    if(j==lenp){
      arr[cnt]=i-lenp;
      cnt++;
      j = failure[j-1]+1;
      continue;
    }
    if(i==lens) break;
    if(string[i] == pat[j]) { i++; j++; }
    else if(j == 0) i++;
    else j = failure[j-1] + 1;
  }
  return cnt;
}

