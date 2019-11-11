#include<bits/stdc++.h>

using namespace std;

vector<int> p;
vector<int> r;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void make_set(int v) {
    p[v] = v;
    r[v] = 0;
}

int find_set(int v) {
    if(v == p[v]) {
        return p[v];
    }
    return p[v] = find_set(p[v]);
}

void union_set(int u, int v) {
    u = find_set(u);
    v = find_set(v);

    if(u != v){
        if(r[u] < r[v]) {
            swap(u, v);
        }
        p[v] = u;
        if(r[u] == r[v]) {
            ++r[u];
        }
    }
}

int main() {
    system("clear");
    int option = 1, x, y;
    p.resize(10);
    r.resize(10);
    while(option) {
        cout << "1. Make Set\n";
        cout << "2. Union\n";
        cout << "3. Find\n";
        cout << "0. Exit\n";
        cout << "Choose any option ";
        cin >> option;
        
        switch(option) {
            case 0:
                break;
            case 1:
                cout << "Enter any integer ";
                cin >> x;
                make_set(x);
                break;
            case 2:
                cout << "Enter 2 integers\n";
                cin >> x >> y;
                union_set(x, y);
                break;
            case 3:
                cout << "Enter any integer ";
                cin >> x;
                cout << find_set(x) << '\n';
                break;
            default:
                cout << "Enter a valid option\n";
        }
        cout << '\n';
    }
    return 0;
}