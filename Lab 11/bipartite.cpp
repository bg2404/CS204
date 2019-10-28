#include<bits/stdc++.h>

using namespace std;

class Graph {
    vector<vector<int>> adj;
    vector<int> color;
    int V;
public:
    Graph(int V) {
        this->V = V;
        for(int i = 0; i < V; ++i) {
            adj.push_back(vector<int>{});
        };
        color.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool DFSUtil(bool visited[], int v, int c) {
        visited[v] = true;
        color[v] = c;
        c ^= 1;
        bool possible = true;;
        for(int i = 0; i < adj[v].size(); ++i) {
            if(!visited[adj[v][i]]) {
                possible = DFSUtil(visited, adj[v][i], c);
                if(!possible) {
                    break;
                }
            }
            else {
                if(c != color[adj[v][i]]) {
                    return false;
                }
            }
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
    int n, m, u, v;
    cin >> n >> m;
    Graph g(n);
    for(int i = 0; i < m; ++i) {
        cin >> u >> v;
        g.addEdge(u, v);
    }
    if(g.DFS()) cout << "YES" << '\n';
    else cout << "NO\n";
    return 0;
}