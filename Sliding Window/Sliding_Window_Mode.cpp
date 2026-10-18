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
    map<int, set<int>> wnd_ifm;


    for(int j=0;j<n;j++) {
        int old = freq[arr[j]]++;

        if(old > 0) {
            wnd_ifm[old].erase(arr[j]);
        }
        if(wnd_ifm[old].empty()) {
            wnd_ifm.erase(old);
        }

        wnd_ifm[old+1].insert(arr[j]);

        if(j-i+1 < k)
            continue;
        else {
            auto [_, ele] = *rbegin(wnd_ifm);
            cout << *begin(ele) << " ";

            int fr = freq[arr[i]]--;
            if(freq[arr[i]] == 0) {
                freq.erase(arr[i]);
            }

            wnd_ifm[fr].erase(arr[i]);
            if(wnd_ifm[fr].empty()) {
                wnd_ifm.erase(fr);
            }
            if(fr > 1) {
                wnd_ifm[fr-1].insert(arr[i]);
            }


            i++;
        }
    }

    return 0;
}
