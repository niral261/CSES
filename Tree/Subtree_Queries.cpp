#include<bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n;
    vector<long long> tree;

    void build(int node, int start, int end, vector<long long>& flat_arr) {
        if(start==end) {
            tree[node] = flat_arr[start];
            return;
        }
        int mid = start + (end-start)/2;
        build(2*node,start,mid,flat_arr);
        build(2*node+1,mid+1,end,flat_arr);
        
        tree[node] = tree[2*node] + tree[2*node+1];
    }
public:
    SegmentTree(int size, vector<long long>& flat_arr) {
        n = size;
        tree.assign(4*n+1,0);
        build(1,1,n,flat_arr);
    }

    void update(int node, int start, int end, int idx, long long val) {
        if(start==end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    long long query(int node, int start, int end, int l, int r) {
        if(r<start || l>end){
            return 0;
        }
        if(l<=start && end<=r) {
            return tree[node];
        }
        int mid = start + (end-start)/2;
        long long left_sum = query(2*node, start, mid, l, r);
        long long right_sum = query(2*node+1, mid+1, end, l, r);

        return left_sum + right_sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<long long> val(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tin(n+1);
    vector<int> tout(n+1);
    int timer = 0;

    auto dfs = [&](auto& self, int u, int p) -> void {
        tin[u] = ++timer;
        for(int v: adj[u]) {
            if(v!=p) {
                self(self,v,u);
            }
        }
        tout[u] = timer;
    };

    dfs(dfs, 1, 0);

    vector<long long> flat_arr(n+1, 0);
    for(int i=1;i<=n;i++) {
        flat_arr[tin[i]] = val[i];
    }

    SegmentTree st(n, flat_arr);

    for(int i=0;i<q;i++) {
        int type;
        cin >> type;

        if(type==1) {
            int s;
            long long x;
            cin >> s >> x;
            st.update(1,1,n,tin[s],x);
        }
        else if(type==2) {
            int s;
            cin >> s;
            cout << st.query(1,1,n,tin[s],tout[s]) << "\n"; 
        }
    } 

    return 0; 
}