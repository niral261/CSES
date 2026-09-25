#include <bits/stdc++.h>
using namespace std;

// Segment Tree for Point Addition and Range Sum
class SegmentTree {
private:
    int max_val;
    vector<int> tree;

    void add(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] += val; // Add the value (don't replace)
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            add(2 * node, start, mid, idx, val);
        } else {
            add(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end || l > r) {
            return 0; // Out of bounds or invalid range
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        return query(2 * node, start, mid, l, r) + 
               query(2 * node + 1, mid + 1, end, l, r);
    }

public:
    SegmentTree(int size) {
        max_val = size;
        tree.assign(4 * max_val + 1, 0); // Initializes to all 0s
    }

    void add(int idx, int val) {
        add(1, 0, max_val, idx, val); // Depths can be 0, so start at 0
    }

    int query(int l, int r) {
        return query(1, 0, max_val, l, r);
    }
};

const int MAXN = 200005;
int n, k1, k2;
vector<vector<int>> adj;
vector<bool> removed_node;
vector<int> subtree_size;
long long total_paths = 0;

SegmentTree* st; // Global pointer to our Segment Tree

void get_sizes(int u, int p) {
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            get_sizes(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }
}

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

// Pass 1: Walk the branch and query the Segment Tree for valid paths
void process_query(int u, int p, int d) {
    if (d > k2) return; // Ignore nodes that are already too deep
    
    int min_req = max(0, k1 - d);
    int max_req = k2 - d;
    
    // Only query if the required range is logically valid
    if (max_req >= min_req) {
        total_paths += st->query(min_req, max_req);
    }
    
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            process_query(v, u, d + 1);
        }
    }
}

// Pass 2 (and Cleanup): Walk the branch and add/remove its nodes
void process_update(int u, int p, int d, int delta) {
    if (d > k2) return;
    
    st->add(d, delta);
    
    for (int v : adj[u]) {
        if (v != p && !removed_node[v]) {
            process_update(v, u, d + 1, delta);
        }
    }
}

void centroid_decomp(int node) {
    get_sizes(node, 0);
    int centroid = get_centroid(node, 0, subtree_size[node]);

    // The centroid itself is at distance 0. We add it to our Segment Tree.
    st->add(0, 1);

    for (int v : adj[centroid]) {
        if (!removed_node[v]) {
            // First check this branch against history
            process_query(v, centroid, 1);
            // Then add this branch into history
            process_update(v, centroid, 1, 1);
        }
    }

    // CLEANUP TRICK:
    // Run the exact same updates, but add -1 to reverse the Segment Tree to 0s!
    st->add(0, -1);
    for (int v : adj[centroid]) {
        if (!removed_node[v]) {
            process_update(v, centroid, 1, -1);
        }
    }

    // Split and recurse
    removed_node[centroid] = true;
    for (int v : adj[centroid]) {
        if (!removed_node[v]) {
            centroid_decomp(v);
        }
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k1 >> k2;
    adj.resize(n + 1);
    removed_node.assign(n + 1, false);
    subtree_size.assign(n + 1, 0);
    
    // Max depth can be at most N. 
    st = new SegmentTree(n + 2);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    centroid_decomp(1);

    cout << total_paths << "\n";

    return 0;
}