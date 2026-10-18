#include<bits/stdc++.h>
using namespace std;

vector<int> seg_tree;

void update(int node, int start, int end, int idx, int val) {
    if(start == end) {
        seg_tree[node] += val;
        return;
    }

    int mid = start + (end - start) / 2;
    if(idx<=mid) {
        update(2*node, start, mid, idx, val);
    } else {
        update(2*node+1, mid+1, end, idx, val);
    }

    seg_tree[node] = seg_tree[2*node] + seg_tree[2*node+1];
}

int query(int node, int start, int end, int l, int r) {
    if(r<start || end<l)
        return 0;
    
    if(l<=start && end<=r) {
        return seg_tree[node];
    }

    int mid = start + (end - start) / 2;
    int left_sum = query(2*node, start, mid, l, r);
    int right_sum = query(2*node+1, mid+1, end, l, r);
    
    return left_sum + right_sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    vector<long long> sorted_arr(n);

    for(int i=0;i<n;i++) {
        cin >> arr[i];
        sorted_arr[i] = arr[i];
    }

    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

    auto get_rank = [&](long long val) {
        return lower_bound(sorted_arr.begin(), sorted_arr.end(), val) - sorted_arr.begin() + 1;
    };

    int max_rank = sorted_arr.size();
    seg_tree.assign(4*max_rank+1, 0);

    long long current_inversions = 0;
    for(int i=0;i<k;i++) {
        int rank = get_rank(arr[i]);
        current_inversions += query(1, 1, max_rank, rank+1, max_rank);
        update(1, 1, max_rank, rank, 1);
    }

    cout << current_inversions << (k == n ? "" : " ");

    for(int i=k;i<n;i++) {
        long long out_val = arr[i-k];
        int out_rank = get_rank(out_val);

        current_inversions -= query(1, 1, max_rank, 1, out_rank-1);
        update(1, 1, max_rank, out_rank, -1);

        long long in_val = arr[i];
        int in_rank = get_rank(in_val);

        current_inversions += query(1, 1, max_rank, in_rank+1, max_rank);
        update(1, 1, max_rank, in_rank, 1);

        cout << current_inversions << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;

}
