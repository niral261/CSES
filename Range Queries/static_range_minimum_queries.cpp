#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> tree;

    void build(vector<int>& arr, int node, int start, int end) {
        if(start==end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);

            tree[node] = min(tree[2*node], tree[2*node+1]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if(r<start || end<l) {
            return INT_MAX;
        }
        
        if(l<=start && end<=r) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left_res = query(2*node, start, mid, l, r);
        int right_res = query(2*node+1, mid+1, end, l, r);

        return min(left_res, right_res);
    }

public: 
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4*n);
        build(arr,1,0,n-1);
    }

    int range_min_query(int l, int r) {
        return query(1,0,n-1,l,r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> x(n);
    for(int i=0;i<n;i++) {
        cin >> x[i];
    }

    SegmentTree seg_tree(x);

    for(int i=0;i<q;i++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << seg_tree.range_min_query(l,r) << "\n";
    }
    cout << endl;
    return 0;
}