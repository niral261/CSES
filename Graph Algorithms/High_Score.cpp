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
    vector<vector<int>> adj(n + 1), rev_adj(n + 1);
    
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].push_back(edges[i].v);
        rev_adj[edges[i].v].push_back(edges[i].u);
    }
    
    // Check reachability from 1 and to n to optimize cycle detection
    vector<bool> reach_from_1(n + 1, false);
    queue<int> q1;
    q1.push(1);
    reach_from_1[1] = true;
    while (!q1.empty()) {
        int u = q1.front();
        q1.pop();
        for (int v : adj[u]) {
            if (!reach_from_1[v]) {
                reach_from_1[v] = true;
                q1.push(v);
            }
        }
    }
    
    vector<bool> reach_to_n(n + 1, false);
    queue<int> qn;
    qn.push(n);
    reach_to_n[n] = true;
    while (!qn.empty()) {
        int u = qn.front();
        qn.pop();
        for (int v : rev_adj[u]) {
            if (!reach_to_n[v]) {
                reach_to_n[v] = true;
                qn.push(v);
            }
        }
    }
    
    vector<long long> dist(n + 1, -INF);
    dist[1] = 0;
    
    // Bellman-Ford relaxations
    for (int i = 1; i <= n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != -INF) {
                dist[edge.v] = max(dist[edge.v], dist[edge.u] + edge.w);
            }
        }
    }
    
    // Check for positive cycles
    bool positive_cycle = false;
    for (const auto& edge : edges) {
        if (dist[edge.u] != -INF && dist[edge.u] + edge.w > dist[edge.v]) {
            if (reach_from_1[edge.v] && reach_to_n[edge.v]) {
                positive_cycle = true;
                break;
            }
        }
    }
    
    if (positive_cycle) {
        cout << -1 << "\n";
    } else {
        cout << dist[n] << "\n";
    }
    
    return 0;
}