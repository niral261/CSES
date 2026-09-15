#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> children(n+1);
    for(int i=2;i<=n;i++) {
        int parent;
        cin >> parent;
        children[parent].push_back(i);
    }

    vector<int> sub(n+1, 0);

    auto dfs =[&](auto&& self, int u) -> int {
        int count = 0;
        for(int v : children[u]) {
            count += 1 + self(self,v);
        }
        sub[u] = count;
        return count;
    };

    dfs(dfs,1);

    for(int i=1;i<=n;i++) {
        cout << sub[i] << (i==n ? '\n' : ' ');
    }
}

