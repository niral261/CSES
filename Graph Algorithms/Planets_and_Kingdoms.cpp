#include <bits/stdc++.h>
using namespace std;

void dfs1(int u, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v, adj, visited, st);
        }
    }
    st.push(u);
}

void dfs2(int u, const vector<vector<int>>& rev_adj, vector<int>& component, int comp_id) {
    component[u] = comp_id;
    for (int v : rev_adj[u]) {
        if (component[v] == 0) {
            dfs2(v, rev_adj, component, comp_id);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    
    vector<bool> visited(n + 1, false);
    stack<int> st;
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs1(i, adj, visited, st);
        }
    }
    
    vector<int> component(n + 1, 0);
    int comp_id = 0;
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        if (component[u] == 0) {
            comp_id++;
            dfs2(u, rev_adj, component, comp_id);
        }
    }
    
    cout << comp_id << "\n";
    for (int i = 1; i <= n; ++i) {
        cout << component[i] << (i == n ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}