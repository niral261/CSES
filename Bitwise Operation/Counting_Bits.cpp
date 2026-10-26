#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    long long total_bits = 0;

    for(int i=0;i<=50;i++) {
        long long blockSize = 1LL << (1+i);
        long long fullBlocks = (n+1) / blockSize;
        long long rem = (n+1) % blockSize;

        total_bits += fullBlocks * (1ll << i);
        if(rem > (1ll << i)) {
            total_bits += rem - (1ll << i);
        }
    }
    cout << total_bits << "\n";
    return 0;
}