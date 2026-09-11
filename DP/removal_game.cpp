#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    long long sum = 0;
    for(int i=0;i<n;i++) {
        cin >> a[i];
        sum += a[i];
    }

    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    for(int i=0;i<n;i++) {
        dp[i][i] = a[i];
    }

    for(int len=2;len<=n;len++) {
        for(int i=0;i<=n-len;i++) {
            int j = i + len - 1;
            dp[i][j] = max(a[i] - dp[i+1][j], a[j] - dp[i][j-1]);
        }
    }

    cout << (sum + dp[0][n-1]) / 2 << endl;
    return 0;
}