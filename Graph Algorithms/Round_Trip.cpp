#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;
int cycle_start = -1, cycle_end = -1;

bool dfs(int u, int p) {
    visited[u] = true;
    parent[u] = p;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        if (visited[v]) {
            cycle_end = u;
            cycle_start = v;
            return true;
        }
        if (!visited[v]) {
            if (dfs(v, u)) return true;
        }
    }
    return false;
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
    parent.assign(n + 1, -1);
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1)) break;
        }
    }
    
    if (cycle_start == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> path;
        path.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(cycle_start);
        
        cout << path.size() << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i + 1 == path.size() ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}