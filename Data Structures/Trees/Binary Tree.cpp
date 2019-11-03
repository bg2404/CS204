#include<bits/stdc++.h>

using namespace std;

struct NODE {
    int data;
    struct NODE* left;
    struct NODE* right;
};

NODE* createNode(int data) {
    NODE* new_node = (struct NODE *) malloc(sizeof(struct NODE));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

NODE* insertNode(NODE* parent, int key, int dir) {
    if(parent == NULL) {
        return createNode(key);
    }
    if(dir > 0) {
        parent->right = createNode(key);
    } else {
        parent->left = createNode(key);
    }
    return parent;
}

void preOrderTraversal(NODE* root) {
    if(root == NULL) return;
    cout << root->data << ' ';
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(NODE* root) {
    if(root == NULL) return;
    inOrderTraversal(root->left);
    cout << root->data << ' ';
    inOrderTraversal(root->right);
}

void postOrderTraversal(NODE* root) {
    if(root == NULL) return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->data << ' ';
}

int main() {

    NODE* root = createNode(1);
    NODE* node[6];
    for(int i = 0; i < 6; ++i) {
        node[i] = createNode(i+2);
    }
    root->left = node[0];                /*                           1                         */
    root->right = node[1];               /*                         /    \                      */ 
    root->left->left = node[2];          /*                       2        3                    */
    root->left->right = node[3];         /*                     /   \    /   \                  */
    root->right->left = node[4];         /*                    4     5  6     7                 */
    root->right->right = node[5];
    cout << "PreOrderTraversal:\t";
    preOrderTraversal(root);
    cout << "\nInOrderTravesal:\t";
    inOrderTraversal(root);
    cout << "\nPostOrderTraversal:\t";
    postOrderTraversal(root);
    cout << '\n';
    return 0;
}