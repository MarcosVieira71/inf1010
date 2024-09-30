#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node{
    int key;
    int subNodes;
    Node* parent;
    Node* right;
    Node* left;
};

Node* searchGreatestValue(Node* root);
Node* createNode(Node* parent, int val);
Node* insertCompleteTree(Node* root, int val);
Node* searchBST(Node* root, int target);
Node* insertBST(Node* root, int val);
Node* deleteNode(Node* root, int target);
Node* flipTree(Node* root);
int countSubNodes(Node* root);
void showTreePreOrder(Node* root);
void showTreePostOrder(Node* root);
void showTreeInOrder(Node* root);
void showTree(Node* root);
void freeTree(Node* root);



int main(void){
  Node* rootComplete = NULL;
  Node* rootBST = NULL;
  int arr[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64};
  printf("val: ");
  for(int i  = 0; i < 10; i++) {
    int val = arr[i];
    printf("%d ", val);
    rootComplete = insertCompleteTree(rootComplete, val);
    rootBST = insertBST(rootBST, val);
  }
  
  printf("\nComplete Tree:\n");
  showTree(rootComplete);
  freeTree(rootComplete);

  printf("\nBST:\n");
  Node* found = searchBST(rootBST, 78);
  Node* found2 = searchBST(rootBST, 24);
  Node* found3 = searchBST(rootBST, 1);
  //rootBST = flipTree(rootBST);
  countSubNodes(rootBST);
  showTree(rootBST);
  deleteNode(rootBST, 41);
  Node* foundGreatest = searchGreatestValue(rootBST);
  showTree(rootBST);
  freeTree(rootBST);

  printf("\n found:\n 1: %p\n 2: %p\n 3: %p\n 4: %p", found, found2, found3, foundGreatest);
  return 0;
}

Node* insertBST(Node* root, int val){
    if(!root) return createNode(NULL, val);
    if(val > root->key){
        if(!root->right)root->right = createNode(root, val);
        else root->right = insertBST(root->right, val);
    }
    else{
        
    if(val < root->key){
        if(!root->left)root->left = createNode(root, val);
        else root->left = insertBST(root->left, val);
    }
    }
    return root;
}

Node* insertCompleteTree(Node* root, int val){
    
    if(!root){
        Node* new = createNode(NULL, val);
        return new;
    }
    Node** queue = (Node**)malloc(sizeof(Node*) * 100);
    int begin = 0, end = 0;
    queue[end++] = root; 
    while(begin < end){
        
        Node* cur = queue[begin++];

        if(!cur->left){
            Node* new = createNode(cur, val);
            cur->left = new;
            break;
        }
        else{
            queue[end++] = cur->left;
        }

        if(!cur->right){
            Node* new = createNode(cur, val);
            cur->right = new;
            break;
        }

        else{
            queue[end++] = cur->right;
        }
    }
    free(queue);
    return root;
}


Node* createNode(Node* parent, int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) return NULL;
    newNode->subNodes = 0;
    newNode->key = val;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->parent = parent;
    return newNode;
}

void showTreePreOrder(Node* root){
    if(!root) return;

    printf("Root -> %p | Parent: %p | Key -> %d\n", root, root->parent, root->key);
    showTreePreOrder(root->left);
    showTreePreOrder(root->right);
}

void showTreePostOrder(Node* root){
    if(!root) return;
    
    showTreePostOrder(root->left);
    showTreePostOrder(root->right);
    printf("Root -> %p | Parent: %p | Key -> %d\n", root, root->parent, root->key);
}

void showTreeInOrder(Node* root){
    if(!root) return;
    
    showTreeInOrder(root->left);
    printf("Root -> %p | Parent -> %p | Key -> %d | Sub-Nodes -> %d\n", root, root->parent, root->key, root->subNodes);
    showTreeInOrder(root->right);
}

void showTree(Node* root){
    // printf("\nShowing tree in pre-order\n");
    // showTreePreOrder(root);
    
    printf("\nShowing tree in order\n");
    showTreeInOrder(root);

    // printf("\nShowing tree in post-order\n");
    // showTreePostOrder(root);
}

void freeTree(Node* root){
    if(!root) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

Node* searchBST(Node* root, int target){
    if(!root) return NULL;
    else{
        if(root->key == target) return root;
        if(root->key > target){
            return searchBST(root->left, target);
        }
        else return searchBST(root->right, target);
    }
}

Node* deleteNode(Node* root, int target){
    if(!root) return NULL;
    if(root->key < target){
        root->right = deleteNode(root->right, target);
    }
    else if(root->key > target){
        root->left = deleteNode(root->left, target);
    }
    else{
        if(!root->left){
            Node* temp = root->right;
            free(root);
            return temp; 
        }
        else if(!root->right){
            Node* temp = root->left;
            free(root);
            return temp; 
        }
        else{
            Node* newRoot = root->right;
            while(newRoot->left){
                newRoot = newRoot->left;
            }

            root->key = newRoot->key;
            root->right = deleteNode(root->right, newRoot->key);
        }
    }
    return root;
}

Node* searchGreatestValue(Node* root){
    if(!root){
        return NULL;
    }

    Node* greatest = root;
    Node* greatestLeft = searchGreatestValue(root->left);
    Node* greatestRight = searchGreatestValue(root->right);
    if (greatestLeft != NULL && greatestLeft->key > greatest->key) greatest = greatestLeft;
    if (greatestRight != NULL && greatestRight->key > greatest->key) greatest = greatestRight;

    return greatest;
}

Node* flipTree(Node* root){
    if(!root) return NULL;
    
    flipTree(root->left);
    flipTree(root->right);
    Node* temp = root->right;
    root->right = root->left;
    root->left = temp; 
    return root;
}

int countSubNodes(Node* root){
    if(!root) return 0;
    
    int leftSubNodes = 0, rightSubNodes = 0;
    if (root->left) {
        leftSubNodes = countSubNodes(root->left);
    }
    if (root->right) {
        rightSubNodes = countSubNodes(root->right);
    }
    root->subNodes = leftSubNodes + rightSubNodes;
    return root->subNodes + 1;
}