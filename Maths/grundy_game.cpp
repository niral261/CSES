#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2000;
vector<int> grundy(MAXN,0);

int getMEX(vector<int>& v) {
    unordered_set<int> s(v.begin(), v.end());
    int mex = 0;
    while(s.find(mex) != s.end()) {
        mex++;
    }

    return mex;
}

void precompute_grundy() {
    // States 0, 1, 2 cannot be split into two unequal heaps, so grundy[0]=grundy[1]=grundy[2] = 0
    grundy[0] = grundy[1] = grundy[2] = 0; 
    for(int i=3;i<MAXN;i++) {
        vector<int> transitions;
        for(int j=1;i-j>j;j++) {
            transitions.push_back(grundy[j]^grundy[i-j]);
        }
        grundy[i] = getMEX(transitions);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    precompute_grundy();


    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        if(n>=MAXN) {
            cout << "first" << endl;
            continue;
        } else {
            if(grundy[n] > 0) {
                cout << "first" << endl;
            } else {
                cout << "second" << endl;
            }
        }
    }

    return 0;
}