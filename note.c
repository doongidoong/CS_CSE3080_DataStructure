#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node { 
 char data; 
 struct node *left_child, *right_child; 
}; 
typedef struct node *tree_pointer; 
tree_pointer create_tree_node(char data) { 
 tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node)); 
 ptr->data = data; 
 ptr->left_child = NULL; 
 ptr->right_child = NULL; 
 return ptr; 
} 
void recursive_inorder(tree_pointer ptr) { 
    if(ptr){
        recursive_inorder(ptr->left_child);
        printf("%c ",ptr->data);
        recursive_inorder(ptr->left_child);
    }
}
void recursive_postorder(tree_pointer ptr) { 
    if(ptr){
        recursive_inorder(ptr->left_child);
        recursive_inorder(ptr->left_child);
        printf("%c ",ptr->data);
    }
} 
void main() { 
 /* create a tree that represents an arithmetic expression */ 
 tree_pointer ptr, ptr1, ptr2; 
 ptr1 = create_tree_node('A'); 
 ptr2 = create_tree_node('B'); 
 ptr = create_tree_node('/'); 
 ptr->left_child = ptr1; 
 ptr->right_child = ptr2; 
 ptr1 = ptr; 
 ptr2 = create_tree_node('C'); 
 ptr = create_tree_node('*'); 
 ptr->left_child = ptr1; 
 ptr->right_child = ptr2; 
 ptr1 = ptr; 
 ptr2 = create_tree_node('D'); 
 ptr = create_tree_node('*'); 
 ptr->left_child = ptr1; 
 ptr->right_child = ptr2; 
 ptr1 = ptr; 
 ptr2 = create_tree_node('E'); 
 ptr = create_tree_node('+'); 
 ptr->left_child = ptr1; 
 ptr->right_child = ptr2; 
 /* call traversal functions */ 
 recursive_inorder(ptr); 
 printf("\n"); 
 recursive_postorder(ptr); 
 printf("\n"); 
} 
