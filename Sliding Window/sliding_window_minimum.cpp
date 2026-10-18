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

    int i=0;
    long long ans = 0;
    deque<pair<int, int>> q;
    for(int j=0;j<n;j++) {
        while(!q.empty() && q.back().first > arr[j]) {
            q.pop_back();
        }

        q.push_back({arr[j], j});

        if(j-i+1 < k)
            continue;
        else {
            ans = ans ^ q.front().first;

            if(q.front().second == i) {
                q.pop_front();
            }
            i++;
        }
    }
    cout << ans << "\n";
    return 0;
}