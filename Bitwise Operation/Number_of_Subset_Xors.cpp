#include <bits/stdc++.h>
using namespace std;

class LinearBasis {
private:
    vector<int> basis;
    int basisSize;
public:
    LinearBasis() {
        basis.resize(31, 0);
        basisSize = 0;
    }

    void insert(int num) {
        for(int i=30;i>=0;i--) {
            if((num >> i) & 1) {
                if(basis[i]==0) {
                    basis[i] = num;
                    basisSize++;
                    break;
                } else {
                    num ^= basis[i];
                }
            }
        }
    }

    int get_basis_size() {
        return basisSize;
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

    long long total_diff_xors = 1LL << lb.get_basis_size();
    cout << total_diff_xors << endl;
    
    return 0;
}