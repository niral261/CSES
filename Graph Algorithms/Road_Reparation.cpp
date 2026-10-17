#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    // Adjacency list: adj[u] stores pairs of {v, weight}
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Undirected graph
    }
    
    vector<bool> visited(n + 1, false);
    // Min-heap priority queue storing {weight, node}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    // Start Prim's algorithm from node 1 with an initial edge weight of 0
    pq.push({0, 1});
    
    long long total_cost = 0;
    int nodes_included = 0;
    
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        
        // If the node is already visited, skip it
        if (visited[u]) continue;
        
        visited[u] = true;
        total_cost += w;
        nodes_included++;
        
        // Push all neighboring edges into the priority queue
        for (auto& edge : adj[u]) {
            int v = edge.first;
            long long weight = edge.second;
            if (!visited[v]) {
                pq.push({weight, v});
            }
        }
    }
    
    // If we have included all n nodes, the MST exists
    if (nodes_included == n) {
        cout << total_cost << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}