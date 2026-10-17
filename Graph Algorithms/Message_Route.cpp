#include <bits/stdc++.h>
using namespace std;

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
        adj[v].push_back(u);
    }
    
    vector<bool> visited(n + 1, false);
    vector<int> parent(n + 1, -1);
    queue<int> q;
    
    q.push(1);
    visited[1] = true;
    
    bool reached = false;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        if (u == n) {
            reached = true;
            break;
        }
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    
    if (!reached) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> path;
        int curr = n;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        
        cout << path.size() << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i + 1 == path.size() ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}