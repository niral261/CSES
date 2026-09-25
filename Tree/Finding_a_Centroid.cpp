#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> subtree_size(n + 1, 0);

    // Step 1: DFS to calculate the size of every subtree
    auto get_sizes = [&](auto&& self, int u, int p) -> void {
        subtree_size[u] = 1; // Count itself
        for (int v : adj[u]) {
            if (v != p) {
                self(self, v, u);
                subtree_size[u] += subtree_size[v]; // Add child's subtree size
            }
        }
    };

    // Step 2: DFS to walk down the tree and find the centroid
    auto get_centroid = [&](auto&& self, int u, int p) -> int {
        for (int v : adj[u]) {
            if (v != p) {
                // If a child has more than half the total nodes, 
                // the centroid MUST be in that child's direction.
                if (subtree_size[v] > n / 2) {
                    return self(self, v, u);
                }
            }
        }
        // If no child has > N/2 nodes, this node is the centroid!
        return u;
    };

    // Build the sizes starting from arbitrary root 1
    get_sizes(get_sizes, 1, 0);

    // Hunt for the centroid starting from root 1
    cout << get_centroid(get_centroid, 1, 0) << "\n";

    return 0;
}