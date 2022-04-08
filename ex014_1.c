#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* strnins(char* s, char* t, int pos) { 
 char *str; 
 int i; 
 if(pos < 0 || pos > strlen(s)) { 
 fprintf(stderr, "pos is out    of bounds.\n"); 
 exit(1); 
 } 
 str = (char*)malloc(strlen(s) + strlen(t) + 1); 
 for(i=0; i<pos; i++) {
     str[i]=s[i];
 } 
 printf("%s\n", str); 
 for(i=0; i<strlen(t); i++) {
     str[pos+i]=t[i];
 } 
  printf("%s\n", str); 
 for(i=pos; i<strlen(s); i++) {
     str[i+strlen(t)]=s[i]; 
 } 
 return str; 
} 
void main() { 
 char s[] = "amobile"; 
 char t[] = "uto"; 
 char *str = strnins(s, t, 1); 
 printf("%s\n", str); 
} 
