#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct Edge {
    int v;
    long long w;
};

struct State {
    long long dist;
    int u;
    int coupon;
    
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    
    // dist[u][0] = min cost to reach u without coupon
    // dist[u][1] = min cost to reach u with coupon used
    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));
    priority_queue<State, vector<State>, greater<State>> pq;
    
    dist[1][0] = 0;
    pq.push({0, 1, 0});
    
    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        
        long long d = curr.dist;
        int u = curr.u;
        int c = curr.coupon;
        
        if (d > dist[u][c]) continue;
        
        for (auto& edge : adj[u]) {
            int v = edge.v;
            long long w = edge.w;
            
            // Option 1: Travel without using coupon (coupon remains unused)
            if (c == 0 && dist[u][0] + w < dist[v][0]) {
                dist[v][0] = dist[u][0] + w;
                pq.push({dist[v][0], v, 0});
            }
            
            // Option 2: Use coupon on this edge (coupon becomes used)
            if (c == 0 && dist[u][0] + w / 2 < dist[v][1]) {
                dist[v][1] = dist[u][0] + w / 2;
                pq.push({dist[v][1], v, 1});
            }
            
            // Option 3: Coupon was already used previously
            if (c == 1 && dist[u][1] + w < dist[v][1]) {
                dist[v][1] = dist[u][1] + w;
                pq.push({dist[v][1], v, 1});
            }
        }
    }
    
    cout << min(dist[n][0], dist[n][1]) << "\n";
    
    return 0;
}