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

    const long long MOD = 1e9 + 7;
    vector<long long> dp(x + 1);

    dp[0] = 1;
    for(int c : coins) {
        for(int i = 1; i <= x; i++) {
            if(i - c >= 0) {
                dp[i] = (dp[i] + dp[i - c]) % MOD;
            }
        }
    }

    cout << dp[x] << "\n";
    
    return 0;
}

/* Limited Supply of Coins (Bounded Knapsack)
int main() {
    vector<int> pocket = {1,1,2,5};
    int target = 4;

    vector<int> dp(target+1, 0);

    dp[0] = 1;
    for(int coin : pocket) {
        for(int j=target;j>=coin;j--) {
            dp[j] = dp[j] + dp[j-coin];
        }
    }

    cout << "Number of ways to make " << target << " is: " << dp[target] << "\n";
    return 0;
}

*/