#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        vector<int> x(n);
        int xor_sum = 0;
        for(int i=0;i<n;i++) {
            cin >> x[i];
            xor_sum ^= x[i];
        }

        if(xor_sum==0) {
            cout << "second" << endl;
        } else {
            cout << "first" << endl;
        }
    }

    return 0;
}