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

void inorder(treePointer ptr) {//바이너리에서 inorder는 정렬된 print를 보여줌
    if(ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data.key);
        if(ptr->leftChild) printf("L: %d ",ptr->leftChild->data.key);
        if(ptr->rightChild) printf("R: %d ",ptr->rightChild->data.key);
        printf("\n");
        inorder(ptr->rightChild);
    }
}

treePointer modifiedSearch(treePointer node, int k) {
    treePointer parent = NULL;
    while(node) {//같지는 않지만 null이 되면 이제 맨 끝이라는 소리
        if(k == node->data.key) return NULL;//같으면 cacncel이므로 retur null
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
    treePointer temp;
    int which_child;
    int dkey;
    
    // search for the node
    while(node) {
        if(k == node->data.key) break;
        parent = node;
        if(k < node->data.key) {
            node = node->leftChild;
            which_child = LEFT;//이동한 방향을 기억
        }
        else {
            node = node->rightChild;
            which_child = RIGHT;
        }
    }

    // case 1: if the node does not exist, we are done.
    if(node == NULL) return;

    // case 2: if the node is a leaf node, just set the corresponding child field of its parent to NULL and free the node.
    if(node->leftChild == NULL && node->rightChild == NULL) {//자식이 없다 leaf
        if(parent == NULL) { //parent가 없으면 root라는 소리, 
            // this is a root node
            *root = NULL;//root가 사라짐
        }
        else {
            if(which_child == LEFT) parent->leftChild = NULL;
            else parent->rightChild = NULL;
        }
        free(node);
    }

    // case 3: if the node is a non-leaf node with a single child
    else if(node->leftChild == NULL || node->rightChild == NULL) {//둘 중에 하나가 null
        if(node -> leftChild !=NULL){//왼쪽 자식이 있는 경우
            if(parent==NULL){
                *root = node->leftChild;
            }
            else{
                if(which_child==LEFT) parent->leftChild = node ->leftChild;//만약 방향이 왼쪽이라면 parentleft의 왼쪽에 추가
                else parent->rightChild = node ->leftChild;//방향이 오른쪽이면 오른쪽에 추가
            }
        }
        else{ //오른쪽 자식이 있는 경우
            if(parent==NULL){
                *root = node->rightChild;
            }
            else{
                if(which_child==LEFT) parent->leftChild = node ->rightChild;
                else parent->rightChild = node ->rightChild;
            }
        }
    }

    // case 4: if the deleted node is a nonleaf node with two children
    else {
        //왼쪽에서 제일 큰 수를 찾는다.
        //temp is the one with the maximum key in node's left subtree   
        temp = node->leftChild;
        while(temp->rightChild){
            temp = temp->rightChild;
        }
        //dkey is the key will replace the deleted key
        dkey = temp->data.key;
        // delete the root that holds dkey. this is cannot be case 4 
        deleteNode(root,dkey);

        //replace the key of the node dkey 
        node-> data.key =dkey;

    }
}

void main() {
   
    treePointer root = NULL;
    insertNode(&root, 40);
    insertNode(&root, 20);
    insertNode(&root, 60);
    insertNode(&root, 10);
    insertNode(&root, 30);
    insertNode(&root, 50);
    insertNode(&root, 70);
    insertNode(&root, 45);
    insertNode(&root, 55);
    deleteNode(&root,60); 
    deleteNode(&root,55);
    deleteNode(&root,20);
    insertNode(&root, 52);
    inorder(root); printf("\n");
}



