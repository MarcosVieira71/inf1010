#include <stdio.h>
#include <stdlib.h>
#define max(A,B) ((A>B) ? (A):(B))

typedef struct Node {
    int key;
    int pos;
    int h;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->h = 0;
    node->left = node->right = NULL;
    return node;
}

void showTree(Node*root){
    if(!root) return;
    showTree(root->left);
    printf("\n%p | %d\n", root, root->pos);
    showTree(root->right);
}

int getHeight(Node* root){
    if(!root) return -1;
    return root->h;
}

Node* rotateRight(Node* root){

}

Node* rotateLeft(Node* root){
    
}

Node* insertAvl(Node* root, int key){
    if(!root) return newNode(key);
    
    if(key > root->key){
        root->right = insertAvl(root->right,key);
        int hRight = getHeight(root->right);
        int hLeft = getHeight(root->left);
        if(abs(hRight - hLeft) > 1){
            if(key > root->right->key) return rotateLeft(root);
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        } 
        root->h = 1 + max(hLeft, hRight);
    }
    
    if(key < root->key){
        root->left = insertAvl(root->left,key);
        int hRight = getHeight(root->right);
        int hLeft = getHeight(root->left);
        if(abs(hRight - hLeft) > 1){
            if(key < root->left->key) return rotateRight(root);
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        } 
        root->h = 1 + max(hLeft, hRight);
    }    
}


