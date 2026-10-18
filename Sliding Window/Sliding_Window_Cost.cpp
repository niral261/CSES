#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // If the window size is 1, it costs 0 to make a single element equal to itself
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            cout << 0 << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
        return 0;
    }

    multiset<long long> left;  
    multiset<long long> right; 
    
    // Track the sums of both halves dynamically
    long long left_sum = 0;
    long long right_sum = 0;

    auto balance = [&]() {
        while (left.size() > right.size() + 1) {
            auto it = prev(left.end());
            long long val = *it;
            right.insert(val);
            right_sum += val;
            left_sum -= val;
            left.erase(it);
        }
        while (right.size() > left.size()) {
            auto it = right.begin();
            long long val = *it;
            left.insert(val);
            left_sum += val;
            right_sum -= val;
            right.erase(it);
        }
    };

    for (int i = 0; i < n; i++) {
        // 1. Add the new element
        if (left.empty() || arr[i] <= *left.rbegin()) {
            left.insert(arr[i]);
            left_sum += arr[i];
        } else {
            right.insert(arr[i]);
            right_sum += arr[i];
        }
        balance();

        // 2. Remove the element that slid out of the window
        if (i >= k) {
            long long out = arr[i - k];
            auto it = left.find(out);
            if (it != left.end()) {
                left.erase(it);
                left_sum -= out;
            } else {
                right.erase(right.find(out));
                right_sum -= out;
            }
            balance();
        }

        // 3. Calculate and print the cost once our window reaches size k
        if (i >= k - 1) {
            long long median = *left.rbegin();
            long long cost = 0;
            
            if (k % 2 == 0) {
                cost = right_sum - left_sum;
            } else {
                cost = right_sum - left_sum + median;
            }
            
            cout << cost << (i == n - 1 ? "" : " ");
        }
    }
    
    cout << "\n";
    return 0;
}