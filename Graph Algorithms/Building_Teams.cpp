#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> color(n + 1, 0); // 0: unvisited, 1: team 1, 2: team 2
    bool possible = true;
    
    for (int i = 1; i <= n; ++i) {
        if (color[i] == 0) {
            queue<int> q;
            q.push(i);
            color[i] = 1;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : adj[u]) {
                    if (color[v] == 0) {
                        color[v] = 3 - color[u]; // Switches between 1 and 2
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        possible = false;
                        break;
                    }
                }
                if (!possible) break;
            }
        }
        if (!possible) break;
    }
    
    if (!possible) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 1; i <= n; ++i) {
            cout << color[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}