#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

struct SegmentTree {
    int size;
    vector<long long> tree;
    
    SegmentTree(int n) {
        size = n;
        tree.assign(4*n + 1, 0);
    }

    void update(int node, int start, int end, int idx, long long val) {
        if(start==end) {
            tree[node] = (tree[node] + val) % MOD;
            return;
        }

        int mid = start + (end - start) / 2;
        if(start <= idx && idx <= mid) {
            update(2*node, start, mid, idx, val);
        } else {
            update(2*node + 1, mid+1, end, idx, val);
        }

        tree[node] = (tree[2*node] + tree[2*node + 1]) % MOD;
    }

    long long query(int node ,int start, int end, int l, int r) {
        if(r < start || end < l) {
            return 0;
        }

        if(l <= start && end <= r) {
            return tree[node];
        }

        int mid = start + (end - start) / 2;
        long long left_sum = query(2*node, start, mid, l, r);
        long long right_sum = query(2*node+1, mid+1, end, l, r);

        return (left_sum + right_sum) % MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);
    vector<int> sorted_unique_arr;

    for(int i=0;i<n;i++) {
        cin >> arr[i];
        sorted_unique_arr.push_back(arr[i]);
    }

    sort(sorted_unique_arr.begin(), sorted_unique_arr.end());
    sorted_unique_arr.erase(unique(sorted_unique_arr.begin(), sorted_unique_arr.end()), sorted_unique_arr.end());

    int unique_count = sorted_unique_arr.size();

    SegmentTree segTree(unique_count);

    long long total = 0;

    for(int i=0;i<n;i++) {
        int rank = lower_bound(sorted_unique_arr.begin(), sorted_unique_arr.end(), arr[i]) - sorted_unique_arr.begin() + 1;

        long long sum_prev_dp = 0;
        if(rank > 1) {
            sum_prev_dp = segTree.query(1,1,unique_count,1,rank-1);
        }

        long long curr_dp = (sum_prev_dp + 1) % MOD;
        total = (total + curr_dp) % MOD;

        segTree.update(1,1,unique_count,rank,curr_dp);
    }
    cout << total << endl;
    return 0;
}