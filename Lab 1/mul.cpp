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
    a = remove_zeroes(a);
    b = remove_zeroes(b);
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

int mul_char(char a, char b) {
    return (a-'0')*(b-'0');
}

string mul_string_by_char(string a, char ch) {
    string c = "";
    int carry = 0;
    reverse(a.begin(), a.end());

    for(int i = 0; i < a.length(); ++i) {
        int num = mul_char(a[i], ch);
        num = num + carry;
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

string mul_by_10(string a, int i) {
    while(i--) {
        a = a + '0';
    }
    return a;
}

string mul(string a, string b) {
    remove_zeroes(a);
    remove_zeroes(b);
    string c = "0";

    for(int i = b.length()-1; i >= 0; --i) {
        c = add(mul_by_10(mul_string_by_char(a, b[i]), b.length() - i - 1), c);
    }
    c= remove_zeroes(c);
    return c;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        string a, b;
        cin >> a >> b;
        cout << mul(a,b) << '\n';
    }
    return 0;
}