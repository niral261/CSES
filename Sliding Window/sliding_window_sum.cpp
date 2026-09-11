#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k, x, a, b, c;
    cin >> n >> k; 
    cin >> x >> a >> b >> c;

    long long j = x;
    long long res = 0;
    long long tot = x;
    
    for(int i = 1; i < k; i++) {
        j = (j * a + b) % c;
        tot += j;
    }

    long long i = x;
    res = tot;
    
    for(int l = k; l < n; l++) {
        j = (j * a + b) % c;
        tot = tot + j - i;
        i = (i * a + b) % c;
        res ^= tot;
    }
    
    cout << res << "\n";
    return 0;
}