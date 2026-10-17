#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> getPossibleSums(const vector<int>& coins) {
        int max_sum = 0;
        for (int c : coins) max_sum += c;

        // dp[s] = true if sum 's' is reachable
        vector<bool> dp(max_sum + 1, false);
        
        // Base case: sum 0 is always achievable (empty subset)
        dp[0] = true;

        for (int coin : coins) {
            // Traverse backwards to ensure each coin is used at most once
            for (int s = max_sum; s >= coin; --s) {
                if (dp[s - coin]) {
                    dp[s] = true;
                }
            }
        }

        // Collect all achievable positive sums
        vector<int> possible_sums;
        for (int s = 1; s <= max_sum; ++s) {
            if (dp[s]) {
                possible_sums.push_back(s);
            }
        }

        return possible_sums;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> coins(n);
        for (int i = 0; i < n; ++i) {
            cin >> coins[i];
        }

        Solution solver;
        vector<int> ans = solver.getPossibleSums(coins);

        cout << ans.size() << "\n";
        for (int i = 0; i < (int)ans.size(); ++i) {
            cout << ans[i] << (i == (int)ans.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}