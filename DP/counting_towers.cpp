#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6;

long long towers[MAXN + 1];

/**
 * Dynamic Programming State Definitions:
 * - prev_a (State A): Number of ways to build a tower of height i where the top layer
 *                     consists of TWO SEPARATE 1x1 blocks (Split Top).
 * - prev_b (State B): Number of ways to build a tower of height i where the top layer
 *                     consists of ONE UNIFIED 2x1 block (Unified Top).
 */
void precompute() {
    // Base Case for Height N = 1:
    // 1 way with a split top layer [1|1]
    // 1 way with a unified top layer [2]
    long long prev_a = 1; 
    long long prev_b = 1; 
    towers[1] = (prev_a + prev_b) % MOD; // Total ways for height 1 = 2

    for (int i = 2; i <= MAXN; i++) {
        /*
         * Transitions to form a NEW SPLIT TOP (curr_a):
         * From previous SPLIT TOP (prev_a) -> 4 choices:
         *   1. Extend both left and right blocks upward.
         *   2. Extend left block upward, start a new block on the right.
         *   3. Extend right block upward, start a new block on the left.
         *   4. Start new blocks on both left and right.
         * From previous UNIFIED TOP (prev_b) -> 1 choice:
         *   1. Place two new separate 1x1 blocks on top.
         * 
         * Total curr_a = 4 * prev_a + prev_b
         */
        long long curr_a = (4 * prev_a + prev_b) % MOD;

        /*
         * Transitions to form a NEW UNIFIED TOP (curr_b):
         * From previous SPLIT TOP (prev_a) -> 1 choice:
         *   1. Place a new single 2x1 block across both columns.
         * From previous UNIFIED TOP (prev_b) -> 2 choices:
         *   1. Extend the single 2x1 block upward.
         *   2. Place a new single 2x1 block on top.
         * 
         * Total curr_b = prev_a + 2 * prev_b
         */
        long long curr_b = (prev_a + 2 * prev_b) % MOD;
        
        // Total ways for height i = (Split Top ways) + (Unified Top ways)
        towers[i] = (curr_a + curr_b) % MOD;
        
        // Roll state forward for next iteration
        prev_a = curr_a;
        prev_b = curr_b;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    precompute();
    
    int t;
    cin >> t;

    while(t-->0) {
        int n;
        cin >> n; 
        cout << towers[n] << endl;
    }
    return 0;
}