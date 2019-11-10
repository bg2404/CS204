#include<bits/stdc++.h>

using namespace std;

vector<int> p, r;

struct Edge {
    int u;
    int v;
    int w;
    bool operator < (Edge const& b) const {
        return w < b.w;
    }
};

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
    int n, m;
    cin >> n >> m;
    p.resize(n);
    r.resize(n);
    Edge edges[m];
    vector<Edge> requiredEdges;
    for(int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    for(int i = 0; i < n; ++i) {
        make_set(i);
    }

    sort(edges, edges + m);
    int cost = 0;
    for(int i = 0; i < m; ++i) {
        if(find_set(edges[i].u) != find_set(edges[i].v)) {
            cost += edges[i].w;
            requiredEdges.push_back(edges[i]);
            union_set(edges[i].u, edges[i].v);
        }
    }

    cout << cost << '\n';

    return 0;
}