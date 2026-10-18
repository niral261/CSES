#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> current_colors;
vector<int> best_colors_array;
int min_colors_found = 20;

void dfs(int u, int max_c) {
    if(max_c >= min_colors_found)
        return;

    if(u==n) {
        min_colors_found = max_c;
        best_colors_array = current_colors;
        return;
    }

    for(int c=1;c<=max_c+1;c++) {
        bool can_color = true;
        for(int v : adj[u]) {
            if(current_colors[v] == c) {
                can_color = false;
                break;
            }
        }

        if(can_color) {
            current_colors[u] = c;
            dfs(u+1, max(max_c, c));
            current_colors[u] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0; 

    adj.resize(n);
    current_colors.assign(n, 0);

    for(int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0,0);

    cout << min_colors_found << "\n";

    for (int i = 0; i < n; ++i) {
        cout << best_colors_array[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;

}
