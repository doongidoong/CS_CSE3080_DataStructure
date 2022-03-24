#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int nfind(char *string, char *pat);

char str[10000000];
char pat[3000];
int arr[10000000]; 

int main() {
    int rv;
    FILE* fp = fopen("string2.txt", "r");
    if (fp == NULL) {
        printf("file error");
        return 1;
    }
    fgets(str, 10000000, fp);
    FILE* fp2 = fopen("pattern2.txt", "r");
    if (fp2 == NULL) {
        printf("file error");
        return 1;
    }
    fgets(pat, 3000, fp2);
    int *temp = arr;
    rv = nfind(str, pat);
    if(rv == 0) {
      printf("The pattern %s was not found in the string.\n", pat);
    } else {
      printf("%d \n",rv);
      for(int i=0;i<rv;i++) printf("%d ",arr[i]);
    }
    printf("\n");
    fclose(fp);
    fclose(fp2);
    return 0;
}

int nfind(char *string, char *pat) {
  /* try implementing this function yourself! */
  int cnt=0;
  int i,j,start =0 ;
  int lasts = strlen(string)-1;
  int lastp = strlen(pat)-1;
  int endmatch = lastp; 
  for(i=0;endmatch<=lasts;start++,endmatch++){  
    if(string[endmatch]==pat[lastp])
      for(j=0,i=start;j<lastp && string[i]==pat[j];i++,j++);
    if(j==lastp) {
      arr[cnt]=start;
      cnt++;
      j=0;
      } 
  }
  return cnt;
}

