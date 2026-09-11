#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    const int MOD = 1e9 + 7;
    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }

    vector<vector<long long>> dp(n, vector<long long>(m+2));
    
    if(arr[0]==0) {
        for(int x=1;x<=m;x++) {
            dp[0][x] = 1;
        } 
    } else {
        dp[0][arr[0]] = 1;
    }

    for(int i=1;i<n;i++) {
        if(arr[i]==0){
            for(int x=1;x<=m;x++) {
                dp[i][x] = (dp[i-1][x-1] + dp[i-1][x] + dp[i-1][x+1] ) % MOD;
            }
        } else {
            dp[i][arr[i]] = (dp[i-1][arr[i]-1] + dp[i-1][arr[i]] + dp[i-1][arr[i]+1]) % MOD;
        }
    }

    if(arr[n-1]==0){
        long long ans = 0;
        for(int x=1;x<=m;x++) {
            ans = (ans + dp[n-1][x]) % MOD;
        }
        cout << ans;
    } else {
        cout << dp[n-1][arr[n-1]];
    }
    cout << endl;
    return 0;
}