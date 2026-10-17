#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<bool>> visited;

void bfs(int sr, int sc) {
    queue<pair<int, int>> q;
    q.push({sr, sc});
    visited[sr][sc] = true;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == '.' && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
}

int main() {
    // Optimize standard input/output streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    grid.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    
    visited.assign(n, vector<bool>(m, false));
    int rooms = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                rooms++;
                bfs(i, j);
            }
        }
    }
    
    cout << rooms << "\n";
    
    return 0;
}