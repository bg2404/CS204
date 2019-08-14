#include<bits/stdc++.h>

using namespace std;

bool checkBalance(string str) {
    stack<char> s;
    s.push('0');
    bool balance = true;
    for(int i = 0; i < str.length(); ++i) {
        if((str[i] == '(' || str[i] == '{') || (str[i] == '[' || str[i] == '<')) {
            s.push(str[i]);
        } else if(str[i] == ')') {
            if(s.top() != '(') {
                balance = false;
                break;
            } else {
                s.pop();
            }
        } else if(str[i] == '}') {
            if(s.top() != '{') {
                balance = false;
                break;
            } else {
                s.pop();
            }
        } else if(str[i] == ']') {
            if(s.top() != '[') {
                balance = false;
                break;
            } else {
                s.pop();
            }
        } else if(str[i] == '>') {
            if(s.top() != '<') {
                balance = false;
                break;
            } else {
                s.pop();
            }
        } else {
            if(s.top() != '|') {
                s.push(str[i]);
            } else {
                s.pop();
            }
        }
    }
    if(s.size() > 1) {
        balance = false;
    }

    return balance;
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        string s;
        cin >> s;
        if(checkBalance(s)) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
    return 0;
}