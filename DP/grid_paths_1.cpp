#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<vector<char>> arr(n, vector<char>(n));
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    int MOD = 1000000007; 
    
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> arr[i][j];
        }
    }

    if(arr[0][0] == '*'){
        cout << 0 << endl;
        return 0;
    }

    dp[0][0] = 1;

    for(int j=1;j<n;j++) {
        if(arr[0][j]=='.' && dp[0][j-1]==1){
            dp[0][j] = 1;
        } else {
            dp[0][j] = 0;
        }
    }

    for(int i=1;i<n;i++) {
        if(arr[i][0]=='.' && dp[i-1][0]==1){
            dp[i][0] = 1;
        } else {
            dp[i][0] = 0;
        }
    }

    for(int i=1;i<n;i++) {
        for(int j=1;j<n;j++) {
           if(arr[i][j] == '.') {
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD; 
            } else {
                dp[i][j] = 0; 
            }
        }
    }
    
    cout << dp[n-1][n-1] << endl;
    return 0;
}