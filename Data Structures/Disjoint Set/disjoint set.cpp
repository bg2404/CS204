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
    r[v] = 1;
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
        r[u] = r[u] + r[v];
    }
}

int main()
{
    int n;
    cin >> n;
    p.resize(2*n+1, 0);
    r.resize(2*n+1, 0);
    r[0] = 300000;
    vector<vector<int>> gb(n);
    for(int i = 0; i <= 2*n; ++i) {
        make_set(i);
    }
    int u, v;
    for(int i = 0; i < n; ++i) {
        cin >> u >> v;
        union_set(u, v);
    }
    int min, max;
    min = 3000000;
    max = 2;
    for(int i = 1; i <= 2*n; ++i) {
        int rank = r[find_set(i)];
        if(rank < min && rank > 1) min = rank;
        if(rank > max) max = rank;
    }
    cout << min << " " << max;
    return 0;
}

/*

There are 2N values to represent nodes in a graph. They are divided into two sets G and B. Each set has exactly N values. Set G is represent by {G[1], G[2],...,G[N]}. G can contain any value between 1 to N(inclusive). Set B is represented by {B[1], B[2],...,B[N]}. B can contain any value between N+1 to 2N(inclusive). Same value can be chosen any number of times.
Here (G[1],B[1]), (G[2],B[2]),...,(G[N],B[N]) represents the edges of the graph.
Your task is to print the number of vertices in the smallest and the largest connected components of the graph.

Note
Single nodes should not be considered in the answer.

Input Format
First line contains an integer .
Each of the next  lines contain two space-separated integers,  line contains  and .

Constraints
1 <= N <= 15000
1 <= G[i] <= N
N+1 <= B[i] <= 2*N

Output Format
Print two space separated integers, the number of vertices in the smallest and the largest components.

Sample Input
5
1 6 
2 7
3 8
4 9
2 6

Sample Output
2 4

*/