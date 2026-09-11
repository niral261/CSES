#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    const long long INF = 1e18;
    vector<long long> dp(x + 1, INF);

    dp[0] = 0;
    for(int i = 1; i <= x; i++) {
        for(int c : coins) {
            if(i - c >= 0) {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }

    if(dp[x] >= INF) {
        cout << -1 << "\n";
    } else {
        cout << dp[x] << "\n";
    }
    return 0;
}