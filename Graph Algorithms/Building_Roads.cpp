#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> n >> m)) return 0;
    
    adj.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    visited.assign(n + 1, false);
    vector<int> representatives;
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            representatives.push_back(i);
            dfs(i);
        }
    }
    
    int roads_to_add = representatives.size() - 1;
    cout << roads_to_add << "\n";
    
    for (size_t i = 0; i < roads_to_add; ++i) {
        cout << representatives[i] << " " << representatives[i + 1] << "\n";
    }
    
    return 0;
}