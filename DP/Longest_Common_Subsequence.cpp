#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LCSSolver {
public:
    void solve() {
        int n, m;
        if (!(cin >> n >> m)) return;

        vector<int> a(n), b(m);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < m; ++i) cin >> b[i];

        // dp[i][j] stores the length of LCS of a[0..i-1] and b[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (a[i - 1] == b[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Backtrack to reconstruct the LCS sequence
        vector<int> lcs;
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (a[i - 1] == b[j - 1]) {
                lcs.push_back(a[i - 1]);
                --i;
                --j;
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                --i;
            } else {
                --j;
            }
        }

        // Reverse to get sequence from left to right
        reverse(lcs.begin(), lcs.end());

        // Output length
        cout << lcs.size() << "\n";

        // Output sequence elements
        for (size_t idx = 0; idx < lcs.size(); ++idx) {
            cout << lcs[idx] << (idx + 1 == lcs.size() ? "" : " ");
        }
        cout << "\n";
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    LCSSolver solver;
    solver.solve();

    return 0;
}