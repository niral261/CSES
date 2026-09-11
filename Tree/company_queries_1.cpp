#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> up(n+1, vector<int>(19, 0));

    for(int i=2;i<=n;i++) {
        cin >> up[i][0];
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
        int x, k;
        cin >> x >> k;

        for(int j=0;j<19;j++) {
            if((k>>j)&1) {
                x = up[x][j];
                if(x==0) {
                    break;                    
                }
            }
        }
        cout << (x == 0 ? -1 : x) << endl;
    }
    return 0;
}