#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10 
struct listNode { 
 int key; 
 struct listNode *link; 
}; 

struct listNode *first = NULL; 

void addToList(int key) { 
 struct listNode *newNode; 
 struct listNode *currNode, *prevNode = NULL; 
 if(first == NULL) { 
    newNode = malloc(sizeof(struct listNode)); 
    newNode->key = key; 
    newNode->link = NULL; 
    first = newNode; 
    return; 
 } 
 currNode = first; 
 while(1) { 
     if(key == currNode->key) return;
     if(currNode->link) currNode = currNode->link;
     else break;
 } 
 newNode = malloc(sizeof(struct listNode)); 
 newNode->key = key; 
 newNode->link = NULL; 
 currNode->link = newNode; 
} 
void deleteFromList(int key) { 
 struct listNode *newNode, *prevNode = NULL; 
 struct listNode *currNode; 
 if(first == NULL) return; 
 currNode = first; 
 while(currNode) {
     if(currNode->key ==key) break;
     prevNode = currNode;
     currNode = currNode->link;
 } 
 if(currNode == NULL) return; 
 
 if(prevNode != NULL) { 
 prevNode->link = currNode->link; 
 } 
 if(currNode == first) { 
 first = first->link; 
 } 
 free(currNode); 
} 
void printList() { 
 struct listNode *currNode; 
 currNode = first; 
 while(currNode){
     printf("%d ", currNode->key);
     currNode= currNode->link;
 }
 printf("\n");
} 
void clearList() { 
 struct listNode *temp; 
 while(first){
     temp =first;
     first= first->link;
     free(temp);
     
 }
} 
void main() { 
 addToList(10); 
 addToList(7); 
 addToList(10); 
 addToList(5); 
 addToList(15); 
 printList(); 
 deleteFromList(5); 
 deleteFromList(10); 
 deleteFromList(8); 
 printList(); 
 
 clearList(); 
} 
