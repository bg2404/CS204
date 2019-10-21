#include<bits/stdc++.h>

using namespace std;

int m, n;

class Graph
{
    int V;
    list<int> *adj;
    int DFSUtil(int v, bool visited[], int count);
public:
    Graph(int V);
    void addEdge(int v, int w);
    int DFS();
};
  
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

int Graph::DFSUtil(int v, bool visited[], int count) {
    visited[v] = true;
    count++;
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            count = DFSUtil(*i, visited, count);
    return count;
}
  
int Graph::DFS() {
    bool *visited = new bool[V]; 
    for(int v = 0; v < V; v++) 
        visited[v] = false;
    
    int max_count = 0;
    for (int v=0; v<V; v++) 
    { 
        if (visited[v] == false) 
        {
            int count = DFSUtil(v, visited, 0);
            max_count = max(count, max_count);
        } 
    }
    return max_count;
}

int convert(int x, int y) {
    return n*x + y;
}

int main() {
    cin >> m >> n;
    int adj[m+1][n+1];
    memset(adj, -1, sizeof(adj));
    int k;
    cin >> k;
    int x, y;
    for(int i = 0; i < k; ++i) {
        cin >> x >> y;
        adj[x][y] = 1;
    }

    Graph G(m*n);

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if(adj[i][j] == adj[i][j+1] && adj[i][j] == 1) {
                G.addEdge(convert(i, j), convert(i, j + 1));
            }
            if(adj[i][j] == adj[i+1][j] && adj[i][j] == 1) {
                G.addEdge(convert(i, j), convert(i + 1, j));
            }
        }
    }

    cout << G.DFS() << '\n';
    
    return 0;
}