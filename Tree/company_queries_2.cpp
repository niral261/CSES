#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> up(n+1, vector<int>(19, 0));
    vector<int> depth(n+1, 0);

    for(int i=2;i<=n;i++) {
        cin >> up[i][0];
        depth[i] = depth[up[i][0]] + 1;
    }

    for(int j=1;j<19;j++) {
        for(int i=1;i<=n;i++) {
            int p = up[i][j-1];
            if(p!=0) {
                up[i][j] = up[p][j-1];
            }
        }
    }

    while(q--) {
        int a, b;
        cin >> a >> b;

        if(depth[a] < depth[b]) swap(a,b);

        int diff = depth[a] - depth[b];
        for(int j=0;j<19;j++) {
            if((diff>>j)&1) {
                a = up[a][j];
            }
        }

        if(a==b) {
            cout << a << endl;
            continue;
        }

        for(int j=18;j>=0;j--) {
            if(up[a][j] != up[b][j]) {
                a = up[a][j]; b= up[b][j];
            }
        }
        cout << up[a][0] << endl;
    }
    return 0;
}