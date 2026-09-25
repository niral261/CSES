#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Build the tree as an adjacency list
    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // dp0[u]: Max matching in subtree u if node u is NOT matched with any of its children
    // dp1[u]: Max matching in subtree u if node u is matched with exactly one child
    vector<int> dp0(n+1), dp1(n+1);
    
    auto dfs = [&](auto&& self, int u, int p) -> void {
        dp0[u] = 0;
        dp1[u] = 0;

        for(int v : adj[u]) {
            if(v!=p) {
                self(self,v,u);
                dp0[u] += max(dp0[v], dp1[v]);
            }
        }

        for(int v : adj[u]) {
            if(v!=p) {
                dp1[u] = max(dp1[u], dp0[u] + dp0[v] + 1 - max(dp0[v], dp1[v]));
            }
        }
    };

    dfs(dfs,1,0);

    cout << max(dp0[1],dp1[1]) << "\n";

    return 0;
}

