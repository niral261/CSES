#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    cin >> n >> k;

    vector<int> basis(31, 0);
    int basisSize = 0;

    for(int i=0;i<n;i++) {
        int x;
        cin >> x;
        for(int j=30;j>=0;j--) {
            if((x >> j) & 1) {
                if(basis[j]==0) {
                    basis[j] = x;
                    basisSize++;
                    break;
                } else {
                    x ^= basis[j];
                }
            }
        }
    }

    // Convert basis to Canonical Form (Reduced Row Echelon Form)
    for(int i=30;i>=0;i--) {
        if(basis[i]) {
            for(int j=i+1;j<=30;j++) {
                if(basis[j] && ((basis[j] >> i) & 1)) {
                    basis[j] ^= basis[i];
                }
            }
        }
    }

    // Collect non-zero basis elements in ascending order
    vector<int> b;
    for(int i=0;i<=30;i++) {
        if(basis[i]) {
            b.push_back(basis[i]);
        }
    }

    // Redundant elements multiplier: 2^(n - basis_size)
    // Capped at k because we never need to output more than k numbers
    long long mult = 1;
    for(int i=0;i<n-basisSize;i++) {
        mult = mult * 2;
        if(mult > k) {
            mult = k;
            break;
        }
    }

    // TO BE COMPLETED: Remaining part of the code
    return 0;
}
