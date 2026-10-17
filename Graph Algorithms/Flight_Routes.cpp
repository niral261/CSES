#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;
    
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    vector<int> count_visited(n + 1, 0);
    
    pq.push({0, 1});
    vector<long long> result;
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        count_visited[u]++;
        
        if (u == n) {
            result.push_back(d);
            if (result.size() == k) break;
        }
        
        if (count_visited[u] > k) continue;
        
        for (auto& edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;
            pq.push({d + w, v});
        }
    }
    
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i + 1 == result.size() ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}