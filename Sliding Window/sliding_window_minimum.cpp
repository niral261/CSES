#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k, x, a, b, c;
    cin >> n >> k; 
    cin >> x >> a >> b >> c;
    
    int capacity = k + 1;
    vector<long long> q_val(capacity);
    vector<int> q_idx(capacity);
    
    int head = 0, tail = 0;

    long long current_x = x;
    long long res = 0;

    for(int i=0;i<n;i++) {
        if(head != tail && q_idx[head] <= i-k) {
            head = (head + 1) % capacity;
        }

        while (head != tail) {
            int back_idx = (tail - 1 + capacity) % capacity;
            
            if (q_val[back_idx] >= current_x) {
                tail = back_idx; 
            } else {
                break;
            }
        }

        q_val[tail] = current_x;
        q_idx[tail] = i;
        tail = (tail + 1) % capacity;

        if(i >= k-1) {
            res ^= q_val[head];
        }

        current_x = (current_x*a + b) % c;
    }
    
    cout << res << "\n";
    return 0;
}