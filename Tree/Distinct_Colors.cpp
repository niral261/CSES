#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O is crucial for this problem to prevent Time Limit Exceeded (TLE)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Read the color of each node
    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    // Build the tree as an adjacency list
    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // colors[u] will store all unique colors in the subtree of node 'u'
    vector<set<int>> colors(n+1);
    vector<int> ans(n+1);
    
    auto dfs = [&](auto&& self, int u, int p) -> void {
        // Step 1: Add the current node's own color to its set
        colors[u].insert(color[u]);

        for(int v : adj[u]) {
            if(v != p) {
                // Process the child subtree fully first
                self(self, v, u);

                // --- SMALL-TO-LARGE MERGING (DSU on Trees) ---
                
                // If the child's set is larger than the parent's set, we swap them. 
                if(colors[v].size() > colors[u].size()) {
                    swap(colors[u], colors[v]);
                }
                
                // Now, colors[v] is guaranteed to be the smaller set.
                // We extract its elements and insert them into the larger set (colors[u]).
                for(int c : colors[v]) {
                    colors[u].insert(c);
                }
                
                // Clear the child's set to free up memory (prevents Memory Limit Exceeded)
                colors[v].clear();
            }
        }
        
        // After merging all children, the size of colors[u] is our final answer for node 'u'
        ans[u] = colors[u].size();
    };

    // Start DFS from root node 1, using 0 as a dummy parent
    dfs(dfs, 1, 0);

    // Print the answers space-separated
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}