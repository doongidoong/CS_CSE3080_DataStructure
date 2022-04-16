#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 100
#define LEFT 0
#define RIGHT 1

typedef struct {
    int key;
} element;

struct node {
    element data;
    struct node *leftChild;
    struct node *rightChild;
};
typedef struct node* treePointer;

void inorder(treePointer ptr) {
    if(ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data.key);
        inorder(ptr->rightChild);
    }
}

treePointer modifiedSearch(treePointer node, int k) {
    treePointer parent = NULL;
    while(node) {
        if(k == node->data.key) return NULL;
        parent = node;
        if(k < node->data.key) node = node->leftChild;
        else node = node->rightChild;
    }
    return parent;
}

void insertNode(treePointer *node, int k) {
    // if the key is already in the tree, do nothing; otherwise add a new node with key k
    treePointer ptr, temp = modifiedSearch(*node, k);
    if(temp || !(*node)) {
        // k is not in the tree
        ptr = (treePointer)malloc(sizeof(*ptr));
        ptr->data.key = k;
        ptr->leftChild = ptr->rightChild = NULL;
        if(*node) {
            if(k < temp->data.key) temp->leftChild = ptr;
            else temp->rightChild = ptr;
        }
        else *node = ptr;
        printf("node with key %d inserted.\n", k);
    } else {
        printf("key %d is already in the tree.\n", k);
    }
}

void deleteNode(treePointer *root, int k) {
    treePointer node = *root;
    treePointer parent = NULL;
    int which_child;
    
    // search for the node
    while(node) {
        if(k == node->data.key) break;
        parent = node;
        if(k < node->data.key) {
            node = node->leftChild;
            which_child = LEFT;
        }
        else {
            node = node->rightChild;
            which_child = RIGHT;
        }
    }

    // case 1: if the node does not exist, we are done.
    if(node == NULL) return;

    // case 2: if the node is a leaf node, just set the corresponding child field of its parent to NULL and free the node.
    if(node->leftChild == NULL && node->rightChild == NULL) {
        if(parent == NULL) {
            // this is a root node
            *root = NULL;
        }
        else {
            if(which_child == LEFT) parent->leftChild = NULL;
            else parent->rightChild = NULL;
        }
        free(node);
    }

    // case 3: if the node is a non-leaf node with a single child
    else if(node->leftChild == NULL || node->rightChild == NULL) {

    }

    // case 4: if the deleted node is a nonleaf node with two children
    else {

    }
}

void main() {
   
    treePointer root = NULL;
    insertNode(&root, 8);
    insertNode(&root, 6);
    insertNode(&root, 9);
    insertNode(&root, 7);
    insertNode(&root, 10);
    insertNode(&root, 7);
    inorder(root); printf("\n");
}



