#include <bits/stdc++.h>
using namespace std;

class LinearBasis {
private:
    vector<int> basis;
public:
    LinearBasis() {
        basis.resize(31, 0);
    }

    void insert(int num) {
        for(int i=30;i>=0;i--) {
            if((num >> i) & 1) {
                if(basis[i]==0) {
                    basis[i] = num;
                    break;
                } else {
                    num ^= basis[i];
                }
            }
        }
    }

    int query() {
        int max_xor = 0;
        for(int i=30;i>=0;i--) {
            if((max_xor ^ basis[i]) > max_xor) {
                max_xor ^= basis[i];
            }
        }
        return max_xor;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    LinearBasis lb;
    for(int i=0;i<n;i++) {
        int x;
        cin >> x;
        lb.insert(x);
    }
    cout << lb.query() << endl;
    
    return 0;
}