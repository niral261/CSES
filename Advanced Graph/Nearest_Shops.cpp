#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<int> shops(k);
    vector<bool> is_shop(n + 1, false);
    for (int i = 0; i < k; ++i) {
        cin >> shops[i];
        is_shop[shops[i]] = true;
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // State arrays to track the closest and second closest shops for each node
    vector<int> d1(n + 1, INF), origin1(n + 1, 0);
    vector<int> d2(n + 1, INF), origin2(n + 1, 0);
    
    // Queue stores pairs of {current_node, origin_shop}
    queue<pair<int, int>> q; 

    // Step 1: Initialize all shops in the queue (Multi-Source Setup)
    for (int s : shops) {
        d1[s] = 0;
        origin1[s] = s;
        q.push({s, s});
    }

    // Step 2: Modified Level-Order Traversal
    while (!q.empty()) {
        int u = q.front().first;
        int orig = q.front().second;
        q.pop();

        // Determine the distance based on whether this origin is the closest or second closest
        int d = (orig == origin1[u]) ? d1[u] : d2[u];

        for (int v : adj[u]) {
            // If we have already recorded this specific origin shop for node v, skip to avoid loops
            if (orig == origin1[v] || orig == origin2[v]) continue;

            // Found a strictly better shortest path from a new origin
            if (d + 1 < d1[v]) {
                d2[v] = d1[v];
                origin2[v] = origin1[v];
                
                d1[v] = d + 1;
                origin1[v] = orig;
                q.push({v, orig});
            } 
            // Found a better second-shortest path from a new origin
            else if (d + 1 < d2[v]) {
                d2[v] = d + 1;
                origin2[v] = orig;
                q.push({v, orig});
            }
        }
    }

    // Step 3: Format the Output
    for (int i = 1; i <= n; ++i) {
        if (is_shop[i]) {
            // If the city itself has a shop, we need the distance to the SECOND closest shop (d2)
            cout << (d2[i] == INF ? -1 : d2[i]) << (i == n ? "" : " ");
        } else {
            // If the city doesn't have a shop, the closest shop (d1) is valid
            cout << (d1[i] == INF ? -1 : d1[i]) << (i == n ? "" : " ");
        }
    }
    cout << "\n";

    return 0;
}