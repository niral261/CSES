#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }
    
    int i=0;
    map<int, int> freq;

    for(int j=0;j<n;j++) {
        freq[arr[j]]++;

        if(j-i+1 < k)
            continue;
        else {
            cout << freq.size() << " ";

            if(freq[arr[i]] == 1) {
                freq.erase(arr[i]);
            } else {
                freq[arr[i]]--;
            }
            i++;
        }
    }

    return 0;
}
