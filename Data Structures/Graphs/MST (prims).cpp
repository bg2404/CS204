#include<bits/stdc++.h>
#define INF 1000000
using namespace std;

int n;

struct Edge {
    int w = INF;
    int to = -1;
    bool operator < (Edge const& b) const {
        return w < b.w;
    }
};

class Graph {
    int V;
    vector<Edge> *adj;
public:
    Graph(int V) {
        this->V = V;
        adj = new vector<Edge>[V];
    }
    void insertEdge(int u, int v, int w);
    int prim();
};

void Graph::insertEdge(int u, int v, int w) {
    adj[u].push_back({w, v});
    adj[v].push_back({w, u});
}

int Graph::prim() {
    int total_weight = 0, s;
    vector<Edge> min_e(n, {INF, -1});
    cin >> s;
    s--;
    min_e[s].w = 0;
    set<Edge> q;
    for(int i = 0; i < n; ++i) {
        q.insert({min_e[i].w, i});
    }
    vector<bool> selected(n, false);
    while(!q.empty()) {

        int v = q.begin()->to;
        selected[v] = true;
        total_weight += q.begin()->w;
        q.erase(q.begin());

        for (auto e : adj[v]) {
            if (!selected[e.to] && e.w < min_e[e.to].w) {
                q.erase({min_e[e.to].w, e.to});
                min_e[e.to] = {e.w, v};
                q.insert({min_e[e.to].w, e.to});
            }
        }
    }
    return total_weight;
}

int main() {

    int m, u, v, w;
    cin >> n >> m;
    Graph G(n);
    for(int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        G.insertEdge(u-1, v-1, w);
    }

    cout << G.prim() << '\n';

    return 0;
}