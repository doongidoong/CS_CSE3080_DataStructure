#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX_STRING_SIZE 10000000
#define MAX_PATTERN_SIZE 3000
int nfind(char *string, char *pat);

char str[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int arr[MAX_STRING_SIZE]; 

int main() {
    int rv;
    FILE* fp = fopen("string.txt", "r");
    if (fp == NULL) {
        printf("the string file does not exist.");
        return 1;
    }
    fgets(str, 10000000, fp);
    FILE* fp2 = fopen("pattern.txt", "r");
    if (fp2 == NULL) {
        printf("the pattern file does not exist.");
        return 1;
    }
    fgets(pat, 3000, fp2);
    int *temp = arr;
    double start_time = (double)clock();
    printf("%lf ",(double)start_time);
    rv = nfind(str, pat);
    double end_time = (double)clock();
    printf("%lf\n",(double)end_time);
    FILE *fp_w= fopen("result_naive.txt","w");
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

int nfind(char *string  , char *pat){
  int cnt=0;
  int strEnd= strlen(string)-1;
  int patEnd = strlen(pat)-1;
  int i,j,start=0;
  int endmatch =patEnd; //첫 endmath는 pat의 길이부터 시작
  for(i=0;endmatch<=strEnd;start++,endmatch++){
    if(string[endmatch]==pat[patEnd]){
      j=0;
      i=start;
      while(1){  //i와 j를 하나씩 올려가면서 문자열과 비교, 만약 다른 게 있다면 반복문을 빠져나옴
        if(string[i]!=pat[j]) break;
        i++;
        j++;
        if(j>=patEnd) break;
      }
      if(j==patEnd) {
        arr[cnt]=start;
        cnt++;
      } 
    }
  }
  return cnt;
}