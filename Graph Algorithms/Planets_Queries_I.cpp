#include <bits/stdc++.h>
using namespace std;

const int LOG = 30; // 2^30 > 10^9, enough to cover max k

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<vector<int>> up(n + 1, vector<int>(LOG));
    for (int i = 1; i <= n; ++i) {
        cin >> up[i][0];
    }
    
    // Precompute the binary lifting sparse table
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    
    // Process queries
    while (q--) {
        int x, k;
        cin >> x >> k;
        for (int j = 0; j < LOG; ++j) {
            if ((k >> j) & 1) {
                x = up[x][j];
            }
        }
        cout << x << "\n";
    }
    
    return 0;
}