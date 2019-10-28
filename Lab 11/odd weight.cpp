#include<bits/stdc++.h>

using namespace std;

class Graph {
    vector<vector<int>> adj;
    vector<int> color;
    int V;
public:
    Graph(int V) {
        this->V = V;
        for(int i = 0; i < V; ++i) adj.push_back(vector<int>{});
        color.resize(V);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool DFSUtil(bool visited[], int v, int c) {
        visited[v] = true;
        color[v] = c;
        bool possible = true;;
        for(int i = 0; i < adj[v].size(); ++i) {
            if(!visited[adj[v][i]]) {
                possible = DFSUtil(visited, adj[v][i], c^1);
                if(!possible) break;
            } else if(c == color[adj[v][i]]) return false;
        }
        return possible;
    }
    bool DFS() {
        bool visited[V];
        memset(visited, false, sizeof(visited));
        for(int i = 0; i < V; ++i) color[i] = -1;
        bool possible = true;
        for(int i = 0; i < V; ++i) {
            if(!visited[i]) {
                possible = DFSUtil(visited, i, 0);
                if(!possible) break;
            }
        }
        return possible;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    int u[m], v[m], e[m], even = -1;
    for(int i = 0; i < m; ++i) {
        cin >> u[i] >> v[i] >> e[i];
        if(!(e[i] & 1)) ++even;
    }
    Graph g(n + even + 1);
    for(int i = 0; i < m; ++i) {
        if(e[i] & 1) {
            g.addEdge(u[i], v[i]);
        } else {
            g.addEdge(u[i], m + even);
            g.addEdge(m + even--, v[i]);
        }
    }
    if(g.DFS()) cout << "NO" << '\n'; else cout << "YES\n";
    return 0;
}