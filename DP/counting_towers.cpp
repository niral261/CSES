#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6;

long long towers[MAXN+1];

void precompute() {
    long long prev_a = 1;
    long long prev_b = 1;
    towers[1] = (prev_a + prev_b) % MOD;

    for(int i=2;i<=MAXN;i++) {
        long long curr_a = (4*prev_a + prev_b) % MOD;
        long long curr_b = (prev_a + 2*prev_b) % MOD;
        
        towers[i] = (curr_a + curr_b) % MOD;
        
        prev_a = curr_a;
        prev_b = curr_b;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    precompute();
    
    int t;
    cin >> t;

    while(t-->0) {
        int n;
        cin >> n; 
        cout << towers[n] << endl;
    }
    return 0;
}