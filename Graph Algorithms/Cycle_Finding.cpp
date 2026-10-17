#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);
    int last_updated_node = -1;
    
    // Run Bellman-Ford for n iterations
    for (int i = 1; i <= n; ++i) {
        last_updated_node = -1;
        for (const auto& edge : edges) {
            if (dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
                parent[edge.v] = edge.u;
                last_updated_node = edge.v;
            }
        }
    }
    
    if (last_updated_node == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        int curr = last_updated_node;
        // Backtrack n times to ensure we are inside the negative cycle
        for (int i = 0; i < n; ++i) {
            curr = parent[curr];
        }
        
        vector<int> cycle;
        int start = curr;
        cycle.push_back(curr);
        curr = parent[curr];
        while (curr != start) {
            cycle.push_back(curr);
            curr = parent[curr];
        }
        cycle.push_back(start);
        reverse(cycle.begin(), cycle.end());
        
        for (size_t i = 0; i < cycle.size(); ++i) {
            cout << cycle[i] << (i + 1 == cycle.size() ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}