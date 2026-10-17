#include <bits/stdc++.h>
using namespace std;

bool dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& in_stack, vector<int>& parent, int& cycle_start, int& cycle_end) {
    visited[u] = true;
    in_stack[u] = true; 
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            if (dfs(v, adj, visited, in_stack, parent, cycle_start, cycle_end)) return true;
        } else if (in_stack[v]) {
            cycle_start = v;
            cycle_end = u;
            return true;
        }
    }
    
    in_stack[u] = false;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    vector<bool> visited(n + 1, false);
    vector<bool> in_stack(n + 1, false);
    vector<int> parent(n + 1, -1);
    int cycle_start = -1, cycle_end = -1;
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            if (dfs(i, adj, visited, in_stack, parent, cycle_start, cycle_end)) break;
        }
    }
    
    if (cycle_start == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());
        
        cout << cycle.size() << "\n";
        for (size_t i = 0; i < cycle.size(); ++i) {
            cout << cycle[i] << (i + 1 == cycle.size() ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}