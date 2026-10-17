#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> adj;
vector<long long> subtree_size;
vector<long long> ans;

// Pass 1: Compute subtree sizes and answer for the arbitrary root (node 1)
void dfs1(int u, int parent, int depth) {
    subtree_size[u] = 1;
    ans[u] = 0; // Contribution of node u to root 1's distance sum

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs1(v, u, depth + 1);
        subtree_size[u] += subtree_size[v];
        ans[u] += ans[v] + subtree_size[v];
    }
}

// Pass 2: Reroot DP - compute answer for all other nodes using parent's answer
void dfs2(int u, int parent) {
    for (int v : adj[u]) {
        if (v == parent) continue;
        
        // Reroot formula:
        ans[v] = ans[u] + n - 2 * subtree_size[v];
        
        dfs2(v, u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    adj.assign(n + 1, vector<int>());
    subtree_size.assign(n + 1, 0);
    ans.assign(n + 1, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Step 1: Compute for root 1
    dfs1(1, 0, 0);

    // Step 2: Propagate to all nodes
    dfs2(1, 0);

    // Print the result for each node from 1 to n
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}