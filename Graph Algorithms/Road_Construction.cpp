#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int Find(vector<int>& par, int n) {
        int p = par[n];
        while(p != par[p]) {
            par[p] = par[par[p]];
            p = par[p];
        }
        return p;
    }

    bool Union(vector<int>& sz, vector<int>& par, int n1, int n2, int& numComponents, int& maxComponentSize) {
        int p1 = Find(par, n1);
        int p2 = Find(par, n2);

        if(p1 == p2) {
            return false;
        }

        // Union by size
        if(sz[p1] < sz[p2]) {
            swap(p1, p2);
        }
        
        par[p2] = p1;
        sz[p1] += sz[p2];
        
        // Update global tracking variables
        maxComponentSize = max(maxComponentSize, sz[p1]);
        numComponents--;
        
        return true;
    }

    void solve() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n, m;
        if (!(cin >> n >> m)) return;

        vector<int> par(n + 1);
        vector<int> sz(n + 1, 1);

        for(int i = 1; i <= n; i++) {
            par[i] = i;
        }

        int numComponents = n;
        int maxComponentSize = 1;

        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            Union(sz, par, u, v, numComponents, maxComponentSize);
            cout << numComponents << " " << maxComponentSize << "\n";
        }
    }
};

int main() {
    Solution sol;
    sol.solve();
    return 0;
}