#include<bits/stdc++.h>

using namespace std;

struct NODE {
    int key;
    NODE* left;
    NODE* right;
    int height;
};

class AVL {
    NODE* root;
    NODE* createNode(int key);
    NODE* insertNodeHelper(NODE* root, int key);
    NODE* leftRotate(NODE* node);
    NODE* rightRotate(NODE* node);
    int getHeight(NODE* node) {
        if(node == NULL) return 0;
        return node->height;
    }
    int getBalance(NODE* node) {
        if(node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    };
    NODE* smallestNode(NODE* root);
    NODE* searchNodeHelper(NODE* root, int key);
    NODE* deleteNodeHelper(NODE* root, int key);
    void print(NODE* node);
public:
    AVL(NODE* root) {
        this->root = root;
    }

    void insertNode(int key);
    NODE* searchNode(int key);
    void deleteNode(int key);
    void printTree();
    NODE* getRoot() {
        return root;
    }

    ~AVL() {
    }
};

NODE* AVL::createNode(int key) {
    NODE* new_node = new NODE;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;
    return new_node;
}

NODE* AVL::leftRotate(NODE* x)
{ 
	NODE* y = x->right;
	NODE* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	return y;
}

NODE* AVL::rightRotate(NODE* y)
{
	NODE *x = y->left;
	NODE *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	return x;
}

NODE* AVL::insertNodeHelper(NODE* node, int key)
{
	if (node == NULL) return(createNode(key));
	if (key < node->key)
		node->left = insertNodeHelper(node->left, key);
	else if (key > node->key)
		node->right = insertNodeHelper(node->right, key);
	else
		return node;
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	int balance = getBalance(node);
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);
	if (balance > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
} 

void AVL::insertNode(int key) {
    NODE* node = createNode(key);
    if(root == NULL) {
        root = node;
        return;
    }
    root = insertNodeHelper(root, key);
}

NODE* AVL::smallestNode(NODE* root) {
    NODE* current = root; 
	while (current->left != NULL) 
		current = current->left; 
	return current;
}

NODE* AVL::searchNodeHelper(NODE* root, int key) {
    if(root == NULL || root->key == key) return root;
    if(root->key < key) return searchNodeHelper(root->right, key);
    return searchNodeHelper(root->left, key);
}

NODE* AVL::searchNode(int key) {
    return searchNodeHelper(root, key);
}

NODE* AVL::deleteNodeHelper(NODE* root, int key) {
    if (root == NULL) return root;
	if ( key < root->key )
		root->left = deleteNodeHelper(root->left, key);
	else if( key > root->key )
		root->right = deleteNodeHelper(root->right, key);
	else {		
        if((root->left == NULL) || (root->right == NULL)) {
			NODE *temp = root->left ? root->left : root->right;
			if (temp == NULL) { 
				temp = root;
				root = NULL;
			}
			else
			    *root = *temp;
			free(temp);
		} else {
			NODE* temp = smallestNode(root->right);
			root->key = temp->key;
			root->right = deleteNodeHelper(root->right, temp->key);
		}
    }

	if (root == NULL) return root;

	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
    if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void AVL::deleteNode(int key) {
    if(root == NULL) {
        return;
    }
    root = deleteNodeHelper(root, key);
}

void AVL::print(NODE* node) {
    if(node != NULL) {
		print(node->left);
        cout << node->key << " ";
		print(node->right);
	}
}

void AVL::printTree() {
	print(root);
}

int main() {
    AVL t1(NULL);
    NODE* node = NULL;
    int option = 1, x;
    while(option) {
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Print\n";
        cout << "4. Search\n";
        cout << "0. Exit\n";
        cout << "Choose any option ";
        cin >> option;
        
        switch(option) {
            case 0:
                break;
            case 1:
                cout << "Enter any integer ";
                cin >> x;
                t1.insertNode(x);
                break;
            case 2:
                cout << "Enter any integer ";
                cin >> x;
                t1.deleteNode(x);
                break;
            case 3:
                t1.printTree();
                break;
            case 4:
                cout << "Enter any integer ";
                cin >> x;
                node = t1.searchNode(x);
                if(node == NULL) cout << "F\n";
                else cout << "T\n";
                break;
            default:
                cout << "Enter a valid option\n";
        }
        cout << '\n';
    }

    return 0;
}