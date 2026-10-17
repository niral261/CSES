#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> topo_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    vector<int> dist(n + 1, -INF);
    vector<int> parent(n + 1, -1);
    dist[1] = 0;
    
    for (int u : topo_order) {
        if (dist[u] != -INF) {
            for (int v : adj[u]) {
                if (dist[u] + 1 > dist[v]) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                }
            }
        }
    }
    
    if (dist[n] < 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << dist[n] + 1 << "\n";
        vector<int> path;
        int curr = n;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i + 1 == path.size() ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}