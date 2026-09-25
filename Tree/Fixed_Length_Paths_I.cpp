#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
int n, k;
vector<vector<int>> adj;

// Variables for Centroid Decomposition
vector<bool> removed_node;
vector<int> subtree_size;
long long total_paths = 0;

// cnt[d] stores the number of nodes at distance 'd' from the current centroid
int cnt[MAXN]; 
int max_depth_so_far = 0;

// Step 1: Calculate subtree sizes (ignoring removed nodes)
void get_sizes(int u, int p) {
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            get_sizes(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }
}

// Step 2: Find the centroid of the current component
int get_centroid(int u, int p, int tree_size) {
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            if (subtree_size[v] > tree_size / 2) {
                return get_centroid(v, u, tree_size);
            }
        }
    }
    return u;
}

// Step 3: DFS to process a branch (either adding to total_paths OR updating cnt array)
void process_branch(int u, int p, bool filling_array, int depth) {
    if (depth > k) return; // We don't care about paths longer than K

    if (filling_array) {
        cnt[depth]++;
        max_depth_so_far = max(max_depth_so_far, depth);
    } else {
        total_paths += cnt[k - depth]; // We found a match!
    }

    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            process_branch(v, u, filling_array, depth + 1);
        }
    }
}

// Main Centroid Decomposition Function
void centroid_decomp(int node) {
    // 1. Get sizes and find the centroid of the current active component
    get_sizes(node, 0);
    int centroid = get_centroid(node, 0, subtree_size[node]);

    // 2. Count paths passing through this centroid
    cnt[0] = 1; // The centroid itself is at distance 0
    max_depth_so_far = 0;

    for (int v : adj[centroid]) {
        if (!removed_node[v]) {
            // First: Count valid paths formed with PREVIOUSLY processed branches
            process_branch(v, centroid, false, 1);
            
            // Second: Add this branch's nodes into the cnt array for FUTURE branches
            process_branch(v, centroid, true, 1);
        }
    }

    // 3. FAST CLEAR: Clean up the cnt array for the next centroid.
    // We only clear up to max_depth_so_far. If we used memset(cnt, 0), it would be O(N^2) and TLE!
    for (int i = 1; i <= max_depth_so_far; i++) {
        cnt[i] = 0;
    }

    // 4. Mark centroid as removed to split the tree
    removed_node[centroid] = true;

    // 5. Recurse into the remaining split components
    for (int v : adj[centroid]) {
        if (!removed_node[v]) {
            centroid_decomp(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    adj.resize(n + 1);
    removed_node.assign(n + 1, false);
    subtree_size.assign(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Start decomposition from node 1
    centroid_decomp(1);

    cout << total_paths << "\n";

    return 0;
}