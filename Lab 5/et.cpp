#include<bits/stdc++.h>

using namespace std;

vector<string> var;
vector<string> val;
vector<string> extracts;
bool assignmentPresent = false;

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
        int present_pos = findInVector(var, value);
        if(present_pos == var.size()) {
            var.push_back(value);
            val.push_back("");
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
            string s = t->value;
            int i;
            for(i = 0; i < var.size(); ++i) {
                if(var[i] == s){
                    break;
                }
            }
            if(i < var.size()) {
                return val[i];
            } else {
                return "";
            }
        }
        return t->value;
    } else {
        if(t->value == "=") {
            int present_pos = findInVector(var, t->left->value);
            string b = solve(t->right);
            if(b == "") {
                return "";
            }
            val[present_pos] = b;
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