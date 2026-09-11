#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k, x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    long long current_x = x;
    long long res = 0;

    long long n_minus_k = n - k;

    for(long long i=0;i<n;i++) {
        long long left_bound = max(0LL, i-k+1);
        long long right_bound = min(n_minus_k, i);

        long long w_count = right_bound - left_bound + 1;
        
        if(w_count%2 == 1)
            res ^= current_x;

        current_x = (current_x*a + b) % c;
    }

    cout << res << "\n";
    return 0;
}


