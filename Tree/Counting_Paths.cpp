#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Binary Lifting Table and Depth array for LCA
    vector<vector<int>> up(n + 1, vector<int>(LOG, 0));
    vector<int> depth(n + 1, 0);

    // Pass 1: Precompute depth and the 2^0 th parent (immediate parent)
    auto build_lca = [&](auto&& self, int u, int p, int d) -> void {
        up[u][0] = p;
        depth[u] = d;
        for (int v : adj[u]) {
            if (v != p) {
                self(self, v, u, d + 1);
            }
        }
    };
    build_lca(build_lca, 1, 0, 0);

    // Fill the Binary Lifting table
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (up[i][j - 1] != 0) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }

    // LCA Function
    auto get_lca = [&](int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        
        // 1. Bring u up to the same depth as v
        int diff = depth[u] - depth[v];
        for (int j = LOG - 1; j >= 0; j--) {
            if ((diff >> j) & 1) {
                u = up[u][j];
            }
        }
        
        if (u == v) return u;
        
        // 2. Move both nodes up together until right below the LCA
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0]; // The parent of the node right below is the LCA
    };

    // Tree Difference Array
    vector<int> val(n + 1, 0);
    
    // Process all M paths
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        int lca = get_lca(a, b);
        
        val[a]++;
        val[b]++;
        val[lca]--;
        if (up[lca][0] != 0) {
            val[up[lca][0]]--; // Parent of LCA
        }
    }

    // Pass 2: Bottom-up prefix sums
    vector<int> ans(n + 1, 0);
    auto dfs_sum = [&](auto&& self, int u, int p) -> void {
        ans[u] = val[u]; // Start with its own difference value
        for (int v : adj[u]) {
            if (v != p) {
                self(self, v, u);
                ans[u] += ans[v]; // Add the sum coming up from children
            }
        }
    };
    dfs_sum(dfs_sum, 1, 0);

    // Print the result
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}