#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

class SegmentTree {
private:
    int n;
    vector<long long> tree;

    void updateInternal(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] = (tree[node] + val) % MOD;
            return;
        }

        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            updateInternal(2 * node, start, mid, idx, val);
        } else {
            updateInternal(2 * node + 1, mid + 1, end, idx, val);
        }

        tree[node] = (tree[2 * node] + tree[2 * node + 1]) % MOD;
    }

    long long queryInternal(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }

        if (l <= start && end <= r) {
            return tree[node];
        }

        int mid = start + (end - start) / 2;
        long long left_sum = queryInternal(2 * node, start, mid, l, r);
        long long right_sum = queryInternal(2 * node + 1, mid + 1, end, l, r);

        return (left_sum + right_sum) % MOD;
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n + 1, 0);
    }

    void update(int idx, long long val) {
        if (idx < 1 || idx > n) return;
        updateInternal(1, 1, n, idx, val);
    }

    long long query(int l, int r) {
        if (l > r || l < 1 || r > n) return 0;
        return queryInternal(1, 1, n, l, r);
    }
};

class Solution {
public:
    long long countIncreasingSubsequences(const vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;

        // Maps arbitrary values to 1-indexed ranks [1...U] to compress the domain for Segment Tree index operations
        vector<int> sorted_unique = arr;
        sort(sorted_unique.begin(), sorted_unique.end());
        sorted_unique.erase(unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

        int unique_count = sorted_unique.size();
        SegmentTree segTree(unique_count);

        long long total = 0;

        for (int i = 0; i < n; i++) {
            int rank = lower_bound(sorted_unique.begin(), sorted_unique.end(), arr[i]) - sorted_unique.begin() + 1;

            // Range sum over [1, rank - 1] aggregates DP counts of all previously seen elements strictly smaller than arr[i]
            long long sum_prev_dp = segTree.query(1, rank - 1);

            // Adding 1 accounts for starting a brand-new subsequence consisting solely of arr[i]
            long long curr_dp = (sum_prev_dp + 1) % MOD;

            total = (total + curr_dp) % MOD;

            // Store curr_dp at 'rank' so future larger elements can extend all subsequences ending at arr[i]
            segTree.update(rank, curr_dp);
        }

        return total;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        Solution solver;
        cout << solver.countIncreasingSubsequences(arr) << "\n";
    }

    return 0;
}