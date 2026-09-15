#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> depth(n+1,0);
    int diameter = 0;
    auto dfs = [&](auto&& self, int u, int p) -> int {
        depth[u] = 0;
        for(int v : adj[u]) {
            if(v!=p) { 
                int c_depth = 1 + self(self,v,u);
                diameter = max(diameter, c_depth + depth[u]);
                depth[u] = max(depth[u],c_depth);
            }
        }
        return depth[u];
    };

    dfs(dfs,1,0);

    cout << diameter << "\n";

    return 0;
}

