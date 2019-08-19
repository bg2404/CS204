#include<bits/stdc++.h>

using namespace std;

string s(int n, char x);

vector<string> extracts;
bool evaluable = true;

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
	if(c == "^") {
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
				string c = st.top(); 
				st.pop(); 
			    postFix.push_back(c); 
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
    string varValue;
    eTree *left, *right;
};

eTree* newNode(string value) {
    eTree *temp = new eTree;
    temp->value = value;
    temp->right = temp->left = NULL;
    temp->isVariable = false;
    temp->varValue = "";
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
            if(postFix[i] != "^") {
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
        return t->value;
    } else {
        string a = solve(t->left);
        string b = solve(t->right);
        int a_int = stoi(a);
        int b_int = stoi(b);
        int ans;
        if(t->value == "+") {
            ans = a_int + b_int;
        } else if(t->value == "-") {
            ans = a_int - b_int;
        } else if(t->value == "*") {
            ans = a_int * b_int;
        } else if(t->value == "/") {
            ans = a_int / b_int;
        } else if(t->value == "^") {
            ans = a_int - b_int;
        } else {

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
        int l;
        cin >> l;
        while(l--) {
            string input;
            cin >> input;
            input = '(' + input + ')';
            for(int i = 1; i < input.size(); ++i) {
                if(input[i] == '-' && input[i-1] == '(') {
                    input[i] = '^';
                }
            }
            extractIVO(input);
            printF(extracts);
            vector<string> postFix = ItoP(extracts);
            printF(postFix);
            eTree *t = makeTree(postFix);
            cout << solve(t);
            cout << '\n';
        }
    }
    return 0;
}