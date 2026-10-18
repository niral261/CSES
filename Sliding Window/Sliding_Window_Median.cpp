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
    
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            cout << arr[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
        return 0;
    }

    multiset<long long> left;
    multiset<long long> right;

    auto balance = [&]() {
        while(left.size() > right.size() + 1) {
            auto it = prev(left.end());
            right.insert(*it);
            left.erase(it);
        }

        while(right.size() > left.size()) {
            auto it = right.begin();
            left.insert(*it);
            right.erase(it);
        }
    };

    for(int i=0;i<n;i++) {
        if(left.empty() || arr[i] <= *rbegin(left)) {
            left.insert(arr[i]);
        } else {
            right.insert(arr[i]);
        }

        balance();

        if(i>=k) {
            long long out = arr[i-k];
            auto it = left.find(out);
            if(it != left.end()) {
                left.erase(it);
            } else {
                right.erase(right.find(out));
            }
            balance();
        }

        if(i>=k-1) {
            cout << *left.rbegin() << (i == n - 1 ? "" : " ");
        }
    }

    cout << "\n";


    return 0;
}
