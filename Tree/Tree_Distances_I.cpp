// Therefore, the algorithm is remarkably simple:

//     Find Node A: Start a Breadth-First Search (BFS) from node 1. 
//                  The farthest node found will be one end of the tree's diameter. 
//                  Let's call this Node A.

//     Find Node B: Run a second BFS starting from Node A. 
//                  The farthest node from A is the other end of the diameter. 
//                  Let's call it Node B. Record the distances from A to all nodes.

//     Get Distances from B: Run a third BFS starting from Node B. 
//                           Record the distances from B to all nodes.


#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    
    if(n==1) {
        cout << 0 << "\n";
        return 0;
    }

    auto bfs = [&](auto&& self, int start) -> pair<int,vector<int>> {
        int furthest = start;
        vector<int> dist(n+1, -1);
        queue<int> q;

        q.push(start);
        dist[start] = 0;

        while(!q.empty()) {
            int u = q.front();
            q.pop();

            for(int v : adj[u]) {
                if(dist[v]==-1) {
                    dist[v] = 1 + dist[u];
                    q.push(v);

                    if(dist[v] > dist[furthest]) {
                        furthest = v;
                    }
                }
            }

        }
        return {furthest,dist};
    };


    pair<int, vector<int>> res1 = bfs(bfs, 1);
    int nodeA = res1.first;

    pair<int, vector<int>> res2 = bfs(bfs, nodeA);
    int nodeB = res2.first;
    vector<int> distA = res2.second;

    pair<int, vector<int>> res3 = bfs(bfs, nodeB);
    vector<int> distB = res3.second;

    for (int i = 1; i <= n; i++) {
        cout << max(distA[i], distB[i]) << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}

