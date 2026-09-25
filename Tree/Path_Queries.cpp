#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n;
    vector<long long> tree;

    void build(int node, int start, int end, const vector<long long>& diff_arr) {
        if (start == end) {
            tree[node] = diff_arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, diff_arr);
        build(2 * node + 1, mid + 1, end, diff_arr);
        
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Notice we use 'add' instead of 'replace' for the difference array
    void add(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] += val; // Add the difference
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

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        long long left_sum = query(2 * node, start, mid, l, r);
        long long right_sum = query(2 * node + 1, mid + 1, end, l, r);

        return left_sum + right_sum;
    }

public:
    SegmentTree(int size, const vector<long long>& diff_arr) {
        n = size;
        tree.assign(4 * n + 1, 0);
        build(1, 1, n, diff_arr);
    }

    void add(int idx, long long val) {
        add(1, 1, n, idx, val);
    }

    long long query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<long long> val(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tin(n + 1);
    vector<int> tout(n + 1);
    int timer = 0;

    // Flatten the tree
    auto dfs = [&](auto&& self, int u, int p) -> void {
        tin[u] = ++timer;
        for (int v : adj[u]) {
            if (v != p) {
                self(self, v, u);
            }
        }
        tout[u] = timer;
    };

    dfs(dfs, 1, 0);

    // Build the initial Difference Array
    // Size is n + 1 to safely handle tout[i] + 1
    vector<long long> diff_arr(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        diff_arr[tin[i]] += val[i];
        if (tout[i] + 1 <= n) {
            diff_arr[tout[i] + 1] -= val[i];
        }
    }

    // Initialize Segment Tree with size 'n'
    SegmentTree st(n, diff_arr);

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;

        if (type == 1) {
            int s;
            long long x;
            cin >> s >> x;
            
            // Calculate how much the value changed
            long long diff = x - val[s];
            
            // Range update using the Difference Array trick (2 point updates)
            st.add(tin[s], diff);
            if (tout[s] + 1 <= n) {
                st.add(tout[s] + 1, -diff);
            }
            
            // Update baseline value
            val[s] = x;
        } 
        else if (type == 2) {
            int s;
            cin >> s;
            
            // Point query using the Difference Array trick (Range sum from 1 to tin[s])
            cout << st.query(1, tin[s]) << "\n";
        }
    }

    return 0;
}