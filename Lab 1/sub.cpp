#include<bits/stdc++.h>

using namespace std;

string remove_zeroes(string a) {
    while(a.length() > 1) {
        if(a[0] == '0') {
            a.erase(a.begin());
        } else {
            break;
        }
    }
    return a;
}

int add_char(char a, char b) {
    return a + b - '0' - '0';
}

void make_length_equal(string &a, string &b) {
    int a_length = a.length();
    int b_length = b.length();

    if(a_length > b_length) {
        while(b_length < a_length) {
            b = '0' + b;
            b_length++;
        }
    } else {
        while(b_length > a_length) {
            a = '0' + a;
            a_length++;
        }
    }
}

string add(string a, string b) {
    string c = "";
    make_length_equal(a,b);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int max_len = max(a.size(), b.size());
    int carry = 0;
    for(int i = 0; i < max_len; ++i) {
        int num = add_char(a[i],b[i]) + carry;
        carry = num / 10;
        num = num % 10;
        c = c + char(num + '0');
    }

    if(carry > 0) {
        c = c + char(carry + '0');
    }

    reverse(c.begin(), c.end());

    return c;
}

bool is_a_greater(string a, string b) {
    a = remove_zeroes(a);
    b = remove_zeroes(b);
    if(a.length() > b.length()) {
        return true;
    } else if(b.length() > a.length()){
        return false;
    } else {
        for(int i = 0; i < a.length(); ++i) {
            if(a[i] < b[i]) {
                return false;
            } else if(a[i] > b[i]) {
                return true;
            }
        }
    }
    return true;
}

string complement10(string a) {
    for(int i = 0; i < a.length(); ++i) {
        a[i] = '9' - a[i] + '0';
    }
    a = add(a, "1");

    return a;
}

string sub(string a, string b) {
    a = remove_zeroes(a);
    b = remove_zeroes(b);
    int n = max(a.length(), b.length());
    bool pos = is_a_greater(a,b);
    if(!pos) {
        string c = a;
        a = b;
        b = c;
    }
    make_length_equal(a,b);
    b = complement10(b);
    string c = add(a,b);
    int c_length = c.length();
    if(c_length > n) {
        while(c_length > n) {
            c.erase(c.begin());
            c_length--;
        }
    }
    c = remove_zeroes(c);
    if(!pos) {
        c = '-' + c;
    }
    return c;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        string a, b;
        cin >> a >> b;
        cout << sub(a,b) << '\n';
    }
    return 0;
}