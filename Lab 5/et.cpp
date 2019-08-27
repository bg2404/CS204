#include<bits/stdc++.h>

using namespace std;

vector<string> var;
vector<string> val;
vector<string> extracts;
bool assignmentPresent = false;

enum color {RED, BLACK};

struct node {
    int color;
    string variable;
    string value;
    struct node* left;
    struct node* right;
    struct node* p;
}*ROOT, *NIL;

struct node* createNode(string variable, string value) {
    struct node* new_node = new struct node;
    new_node->color = RED;
    new_node->variable = variable;
    new_node->value = value;
    new_node->left = NIL;
    new_node->right = NIL;
    new_node->p = NIL;
    return new_node;
}

struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    x->right = y->left;
    if(y->left != NIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if(x->p == NIL) {
        ROOT = y;
    } else if(x->p->left == x) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
    return x;
}

struct node* rightRotate(struct node* x) {
    struct node* y = x->left;
    x->left = y->right;
    if(y->right != NIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if(x->p == NIL) {
        ROOT = y;
    } else if(x->p->left == x) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->right = x;
    x->p = y;
    return x;
}

void insertNodeFixup(struct node* z) {
    while(z->p != NIL && z->p->color == RED) {
        if(z->p == z->p->p->left) {
            struct node* y = z->p->p->right;
            if(y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if(z == z->p->right) {
                    z = z->p;
                    leftRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(z->p->p);
            }
        } else {
            struct node* y = z->p->p->left;
            if(y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if(z == z->p->left) {
                    z = z->p;
                    rightRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(z->p->p);
            }
        }
    }
    ROOT->color = BLACK;
}

void insertNode(string variable, string value) {
    struct node* z = createNode(variable, value);
    struct node* y = NIL;
    struct node* x = ROOT;
    while(x != NIL) {
        y = x;
        if(z->variable < x->variable) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if(y == NIL) {
        ROOT = z;
    } else if(z->variable < y->variable) {
        y->left = z;
    } else {
        y->right = z;
    }
}

struct node* searchNode(struct node* root, string variable) {
    if(root == NIL || variable == root->variable) {
        return root;
    }
    if(variable < root->variable) {
        return searchNode(root->left, variable);
    }
    return searchNode(root->right, variable);
}

int findInVector(vector<string> var, string s) {
    int i;
    for(i = 0; i < var.size(); ++i) {
        if(var[i] == s) {
            break;
        }
    }
    return i;
}
void extractIVO(string str) { 
    extracts.clear();
    stringstream ss;     
    ss << str; 
    char temp; 
    string integer = ""; 
    while (!ss.eof()) { 
        ss >> temp; 
        if(!ss.eof()) {
            if (temp < 48 || temp > 57) {
                if(integer != "") {
                    extracts.push_back(integer);
                    integer = "";
                }
                string s(1,temp);
                extracts.push_back(s);
            } else {
                integer = integer + temp;
            }
        }
    }
    if(integer != "") {
        extracts.push_back(integer);
    }
} 

int precedance(string c) 
{ 
    if(c == "#") {
        return 4;
    }else if(c == "^") {
        return 3;
    } else if(c == "*" || c == "/") {
	    return 2; 
    } else if(c == "+" || c == "-") {
	    return 1; 
    } else if(c == "=") {
        return 0;
    } else {
	    return -1; 
    }
} 

vector<string> ItoP(vector<string> inFix) 
{ 
	stack<string> st; 
    vector<string> postFix;
	st.push("["); 
	int l = extracts.size(); 
	for(int i = 0; i < l; i++) { 
		if(isalnum(inFix[i][0])) {
		    postFix.push_back(inFix[i]);
        } else if(inFix[i] == "(")  {
		    st.push("("); 
        } else if(inFix[i] == ")") { 
			while(st.top() != "[" && st.top() != "(") { 
				string c = st.top(); 
				st.pop(); 
			    postFix.push_back(c); 
			} 
			if(st.top() == "(") { 
				st.pop(); 
			} 
		} else { 
			while(st.top() != "[" && precedance(inFix[i]) <= precedance(st.top())) {
                if(precedance(inFix[i]) == precedance(st.top()) && inFix[i] == "^") {
                    break;
                } else {
                    string c = st.top(); 
                    st.pop();
                    postFix.push_back(c); 
                }
			} 
			st.push(inFix[i]); 
		} 
	}
	while(st.top() != "[") { 
		string c = st.top(); 
		st.pop(); 
		postFix.push_back(c); 
	}

    return postFix;
} 

struct eTree {
    string value;
    bool isVariable;
    eTree *left, *right;
};

eTree* newNode(string value) {
    eTree *temp = new eTree;
    temp->value = value;
    temp->right = temp->left = NULL;
    if(isalpha(value[0])) {
        temp->isVariable = true;
        struct node* f = searchNode(ROOT, value);
        if(f == NIL) {
            insertNode(value, "");
        }
    } else {
        temp->isVariable = false;
    }
    return temp;
}

eTree* makeTree(vector<string> postFix) {
    stack <eTree*> st;
    eTree *t, *t_R, *t_L;

    for(int i = 0; i < postFix.size(); ++i) {
        if(isalnum(postFix[i][0])) {
            t = newNode(postFix[i]);
            st.push(t);
        } else {
            t = newNode(postFix[i]);
            t_R = st.top();
            st.pop();
            if(postFix[i] != "#") {
                t_L = st.top();
                st.pop();
            } else {
                t_L = NULL;
            }

            t->right = t_R;
            t->left = t_L;
            st.push(t);
        }
    }
    t = st.top();
    st.pop();

    return t;
}

string solve(eTree* t) {
    if(t == NULL) {
        return "0";
    }
    if(isalnum((t->value)[0])) {
        if(t->isVariable) {
            struct node* f = searchNode(ROOT, t->value);
            if(f != NIL) {
                return f->value;
            } else {
                return "";
            }
        }
        return t->value;
    } else {
        if(t->value == "=") {
            struct node* f = searchNode(ROOT, t->left->value);
            string b = solve(t->right);
            if(b == "") {
                return "";
            }
            f->value = b;
            assignmentPresent = true;
            return "";
        }
        string a = solve(t->left);
        string b = solve(t->right);
        if(a == "" || b == "") {
            return "";
        }
        long long a_int = stoi(a);
        long long b_int = stoi(b);
        long long ans;
        if(t->value == "+") {
            ans = a_int + b_int;
        } else if(t->value == "-") {
            ans = a_int - b_int;
        } else if(t->value == "*") {
            ans = a_int * b_int;
        } else if(t->value == "/") {
            ans = a_int / b_int;
        } else if(t->value == "#") {
            ans = a_int - b_int;
        } else if(t->value == "^") {
            ans = pow(a_int, b_int);
        }

        return to_string(ans);
    }
}

void printF(vector<string> v) {
    for(int i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        var.clear();
        val.clear();
        int l;
        cin >> l;
        while(l--) {
            assignmentPresent = false;
            string input;
            cin >> input;
            input = '(' + input + ')';
            for(int i = 1; i < input.size(); ++i) {
                if(input[i] == '-' && !isalnum(input[i-1])) {
                    input[i] = '#';
                }
            }
            extractIVO(input);
            vector<string> postFix = ItoP(extracts);
            eTree *t = makeTree(postFix);
            string ans = solve(t);
            if(ans == "") {
                if(!assignmentPresent) {
                    cout << "CANT BE EVALUATED\n";
                }
            } else {
                cout << ans << '\n';
            }
        }
    }
    return 0;
}