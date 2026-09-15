#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<set<int>> colors(n+1);
    vector<int> ans(n+1);
    
    auto dfs = [&](auto&& self, int u, int p) -> void {
        colors[u].insert(color[u]);

        for(int v : adj[u]) {
            if(v!=p) {
                self(self,v,u);

                if(colors[v].size() > colors[u].size())
                    swap(colors[u], colors[v]);
                
                for(int c : colors[v]) {
                    colors[u].insert(c);
                }
                colors[v].clear();
            }
        }
        ans[u] = colors[u].size();
    };

    dfs(dfs,1,0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}

