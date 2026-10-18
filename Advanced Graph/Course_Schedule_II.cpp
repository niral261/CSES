#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Use reversed edges to build the schedule from back to front
    vector<vector<int>> reverse_adj(n + 1);
    vector<int> out_degree(n + 1, 0); 

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b; 
        reverse_adj[b].push_back(a);
        out_degree[a]++; 
    }

    priority_queue<int> pq;
    
    for (int i = 1; i <= n; ++i) {
        if (out_degree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> schedule;

    while (!pq.empty()) {
        int curr = pq.top();
        pq.pop();
        
        schedule.push_back(curr);

        for (int neighbor : reverse_adj[curr]) {
            out_degree[neighbor]--;
            if (out_degree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }

    reverse(schedule.begin(), schedule.end());
    
    for (int i = 0; i < n; ++i) {
        cout << schedule[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}