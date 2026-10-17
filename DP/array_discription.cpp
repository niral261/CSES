#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    const int MOD = 1e9 + 7;
    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // dp[i][x] = number of valid ways to fill the prefix [0...i] such that arr[i] = x
    // Dimension is (m + 2) so indices 0 and m + 1 act as padded boundaries (initialized to 0)
    // This allows dp[i-1][x-1] when x=1 or dp[i-1][x+1] when x=m to run without out-of-bounds checks!
    vector<vector<long long>> dp(n, vector<long long>(m + 2, 0));

    // Base Case for Index 0
    if (arr[0] == 0) {
        // If the first element is unknown (0), it can be any value from 1 to m
        for (int x = 1; x <= m; x++) {
            dp[0][x] = 1;
        }
    } else {
        // If the first element is known, only that fixed value has 1 valid way
        dp[0][arr[0]] = 1;
    }

    // DP Transitions for indices 1 to n - 1
    for (int i = 1; i < n; i++) {
        if (arr[i] == 0) {
            // If current element is unknown, try all possible valid values x from 1 to m
            for (int x = 1; x <= m; x++) {
                dp[i][x] = (dp[i - 1][x - 1] + dp[i - 1][x] + dp[i - 1][x + 1]) % MOD;
            }
        } else {
            // If current element is fixed to arr[i], transition only for x = arr[i]
            int x = arr[i];
            dp[i][x] = (dp[i - 1][x - 1] + dp[i - 1][x] + dp[i - 1][x + 1]) % MOD;
        }
    }

    // Calculate Final Answer
    if (arr[n - 1] == 0) {
        // If last element was unknown, sum over all valid ending values x from 1 to m
        long long ans = 0;
        for (int x = 1; x <= m; x++) {
            ans = (ans + dp[n - 1][x]) % MOD;
        }
        cout << ans;
    } else {
        // If last element was fixed, the answer is just dp[n-1][arr[n-1]]
        cout << dp[n - 1][arr[n - 1]];
    }

    cout << "\n";
    return 0;
}