#include<bits/stdc++.h>

using namespace std;

struct NODE {
    int key;
    NODE* parent;
    NODE* left;
    NODE* right;
};

class BST {
    NODE* root;
    NODE* createNode(int key);
    void insertNodeHelper(NODE* root, NODE* node);
    NODE* smallestNode(NODE* root);
public:
    BST(NODE* root) {
        this->root = root;
    }

    void insertNode(int key);
    void joinTree(BST Tree, NODE* node);
    NODE* searchNode(int key);
    NODE* deleteNode(int key);
    void printTree(NODE* root);
    NODE* getRoot() {
        return root;
    }

    ~BST() {
    }
};

NODE* BST::createNode(int key) {
    NODE* new_node = new NODE;
    new_node->key = key;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void BST::insertNodeHelper(NODE* root, NODE* node) {
    if(node->key > root->key) {
        if(root->right != NULL) {
            insertNodeHelper(root->right, node);
        } else {
            root->right = node;
            node->parent = root;
        }
    } else {
        if(root->left != NULL) {
            insertNodeHelper(root->left, node);
        } else {
            root->left = node;
            node->parent = root;
        }
    }
}

void BST::insertNode(int key) {
    NODE* node = createNode(key);
    if(root == NULL) {
        root = node;
        return;
    }

    insertNodeHelper(root, node);
}

void BST::joinTree(BST tree, NODE* node) {
    NODE *left = NULL, *right = NULL;
    if(tree.getRoot() == NULL) {
        if(root == NULL) {
            root = node;
            root->parent = NULL;
            node->left = node->right = NULL;
        } else {
            node->left = root;
            root->parent = node;
            root = node;
            root->parent =  NULL;
            root->right = NULL;
        }
    }
    else if(root == NULL) {
        node->right = tree.getRoot();
        node->right->parent = node;
        root = node;
        root->left = NULL;
    } else {
        if(root->key > tree.getRoot()->key) {
            left = tree.getRoot();
            right = root;
        } else {
            right = tree.getRoot();
            left = root;
        }
        left->parent = right->parent = node;
        node->left = left;
        node->right = right;
        root = node;
    }
}

NODE* BST::searchNode(int key) {
    NODE* current = root;
    while(current != NULL) {
        if(current->key == key) {
            return current;
        } else if(current->key > key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

NODE* BST::smallestNode(NODE* node) {
    if(node == NULL) {
        return NULL;
    }
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}

NODE* BST::deleteNode(int key) {
    NODE* node = searchNode(key);
    if(node == NULL) {
        return NULL;
    }else if(node->left == NULL && node->right == NULL) {
        if(node == root) {
            root = NULL;
        } else if(node->parent->left == node) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
    } else if(node->left == NULL) {
        if(node == root) {
            root = root->right;
            root->parent = NULL;
        } else if(node->parent->left == node) {
            node->parent->left = node->right;
            node->right->parent = node->parent;
        } else {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
    } else if(node->right == NULL) {
        if(node == root) {
            root = root->left;
            root->parent = NULL;
        } else if(node->parent->left == node) {
            node->parent->left = node->left;
            node->left->parent = node->parent;
        } else {
            node->parent->right = node->left;
            node->left->parent = node->parent;
        }
    } else {
        NODE* joint = smallestNode(node->right);
        BST T1(node->left);
        BST T2(node->right);
        if(joint != NULL) {
            T2.deleteNode(joint->key);
            T1.joinTree(T2, joint);
        } else {

        }
        if(node == root) {
            root = T1.getRoot();;
        } else if(node->parent->left == node) {
            node->parent->left = T1.getRoot();
            T1.getRoot()->parent = node->parent;
        } else {
            node->parent->right = T1.getRoot();
            T1.getRoot()->parent = node->parent;
        }
    }
    return node;
}

void BST::printTree(NODE* root) {
    if(root == NULL) return;
    printTree(root->left);
    cout << root->key << ' ';
    printTree(root->right);
}

int main() {
    BST t1(NULL), t2(NULL);
    t1.insertNode(3);
    t1.insertNode(1);
    t1.insertNode(2);
    NODE* node = new NODE;
    node->key = 4;
    node->left = node->right = NULL;
    t2.insertNode(6);
    t2.insertNode(5);
    t2.insertNode(7);
    if(t1.searchNode(5)) {
        cout << "T";
    } else {
        cout << "F";
    }
    if(t1.searchNode(3)) {
        cout << "T\n";
    } else {
        cout << "F\n";
    }
    t1.printTree(t1.getRoot());
    cout << '\n';

    t1.joinTree(t2, node);
    t1.printTree(t1.getRoot());
    cout << '\n';

    node = t1.deleteNode(3);
    free(node);
    t1.printTree(t1.getRoot());
    cout << '\n';
    return 0;
}