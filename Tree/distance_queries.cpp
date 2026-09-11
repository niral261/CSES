#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 19;

vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN];

void dfs(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;
    
    for(int v : adj[u]) {
        if(v!=p) {
            dfs(v, u, d+1);
        }
    }
}

void init_lca(int n, int node) {
    dfs(node, 0, 0);

    for(int j=1;j<LOG;j++) {
        for(int i=1;i<=n;i++) {
            if(up[i][j-1]!=0)
                up[i][j] = up[up[i][j-1]][j-1];
        }
    }
}

int get_lca(int a, int b) {
    if(depth[a] < depth[b]) swap(a,b);

    int diff = depth[a] - depth[b];
    for(int j=0;j<19;j++) {
        if((diff>>j)&1) {
            a = up[a][j];
        }
    }

    if(a==b) {
        return a;
    }

    for(int j=18;j>=0;j--) {
        if(up[a][j] != up[b][j]) {
            a = up[a][j]; b= up[b][j];
        }
    }

    return up[a][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    for(int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    init_lca(n,1);

    while(q--) {
        int a, b;
        cin >> a >> b;
        int lca = get_lca(a,b);
        int distance = depth[a] + depth[b] - 2*depth[lca];
        cout << distance << endl;
    }
    return 0;
}