#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

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
    
    vector<long long> dp(n + 1, 0);
    dp[1] = 1;
    
    for (int u : topo_order) {
        if (dp[u] > 0) {
            for (int v : adj[u]) {
                dp[v] = (dp[v] + dp[u]) % MOD;
            }
        }
    }
    
    cout << dp[n] << "\n";
    
    return 0;
}