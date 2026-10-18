#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k, x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<long long> arr(n);
    for(int i=0;i<n;i++) {
        if(i==0)
            arr[i] = x;
        else
            arr[i] = (arr[i-1] * a + b) % c;
    }
    
    vector<long long> prefix_ors(n);
    for(int i=0;i<n;i++) {
        if(i%k==0) {
            prefix_ors[i] = arr[i];
        } else {
            prefix_ors[i] = prefix_ors[i-1] | arr[i];
        }
    }

    vector<long long> suffix_ors(n);
    for(int i=n-1;i>=0;i--) {
        if(i%k==k-1) {
            suffix_ors[i] = arr[i];
        } else {
            suffix_ors[i] = suffix_ors[i+1] | arr[i];
        }
    }

    long long ans = 0;
    for(int j=k-1;j<n;j++) {
        long long c_or = prefix_ors[j] | suffix_ors[j-k+1];
        ans ^= c_or;
    }
    cout << ans << "\n";
    return 0;
}
