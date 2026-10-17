#include <bits/stdc++.h>
using namespace std;

void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    
    // Check reachability from city 1 in the original graph
    vector<bool> visited1(n + 1, false);
    dfs(1, adj, visited1);
    
    for (int i = 1; i <= n; ++i) {
        if (!visited1[i]) {
            cout << "NO\n";
            cout << 1 << " " << i << "\n";
            return 0;
        }
    }
    
    // Check reachability to city 1 by traversing the reversed graph from city 1
    vector<bool> visited2(n + 1, false);
    dfs(1, rev_adj, visited2);
    
    for (int i = 1; i <= n; ++i) {
        if (!visited2[i]) {
            cout << "NO\n";
            cout << i << " " << 1 << "\n";
            return 0;
        }
    }
    
    cout << "YES\n";
    
    return 0;
}