#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    long long x[n];
    for(int i=0;i<n;i++) {
        cin >> x[i];
    }

    vector<long long> prefix(n, 0);
    prefix[0] = x[0];
    for(int i=1;i<n;i++) {
        prefix[i] = prefix[i-1] + x[i];
    }

    int l, r;
    for(int i=0;i<q;i++) {
        cin >> l >> r;
        l--;
        r--;
        if (l == 0) {
            cout << prefix[r] << "\n";
        } else {
            cout << prefix[r] - prefix[l-1] << "\n";
        }
    }
    cout << endl;
    return 0;
}