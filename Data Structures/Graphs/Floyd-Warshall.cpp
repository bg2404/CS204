#include<bits/stdc++.h>
#define INF 99999
using namespace std;

int32_t main() {
    int n, m, u, v, w;
    cin >> n >> m;
    int d[n][n];
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            d[i][j] = INF;
        }
    }
    for(int i = 0; i < n; ++i) {
        d[i][i] = 0;
    }
    for(int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        d[--u][--v] = w;
    }

    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }

    int q;
    cin >> q;
    while(q--) {
        cin >> u >> v;
        if(d[--u][--v] == INF) {
            cout << -1 << '\n';
        } else {
            cout << d[u][v] << '\n';
        }
    }
    return 0;
}