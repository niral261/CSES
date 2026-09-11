#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    const int MOD = 1e9 + 7;

    vector<long long> v(n+1);

    for(int i=0;i<=n;i++) {
        if(i==0) {
            v[i] = 1;
        }
        else if(i==1) {
            v[i] = 1;
        }

        else if(i>1 && i<7) {
            v[i] = (2 * v[i-1]) % MOD;
        }

        else {
            v[i] = (v[i-1]*2 - v[i-7] + MOD ) % MOD;
        }
    }
    cout << v[n] << "\n";
    return 0;
}