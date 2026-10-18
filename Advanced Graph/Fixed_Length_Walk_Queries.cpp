#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
int n,m,q;
vector<int> adj[2505];
// dist[start_node][target_node][parity]
int dist[2505][2505][2];
bool computed[2505];

void compute_bfs(int start) {
    computed[start] = true;
    
    queue<pair<int, int>> q;
    dist[start][start][0] = 0;
    q.push({start, 0});

    while(!q.empty()) {
        int node = q.front().first;
        int parity = q.front().second;
        q.pop();

        for(int v : adj[node]) {
            int next_parity = 1 - parity;
            if(dist[start][v][next_parity] == INF) {
                dist[start][v][next_parity] = dist[start][node][parity] + 1;
                q.push({v, next_parity});
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;

    for(int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(dist, 0x3f, sizeof(dist));

    for(int i=1;i<=q;i++) {
        int a, b, x;
        cin >> a >> b >> x;

        if(!computed[a]) {
            compute_bfs(a);
        }

        int target_parity = x % 2;
        if(dist[a][b][target_parity] <= x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}