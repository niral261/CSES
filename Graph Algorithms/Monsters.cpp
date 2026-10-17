#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<string> grid(n);
    int sr = -1, sc = -1;
    queue<pair<int, int>> q;
    vector<vector<int>> monster_time(n, vector<int>(m, INF));
    
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') {
                sr = i; sc = j;
            } else if (grid[i][j] == 'M') {
                monster_time[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char move_char[] = {'U', 'D', 'L', 'R'};
    
    // Step 1: Multi-source BFS for all monsters
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#' && monster_time[nr][nc] == INF) {
                monster_time[nr][nc] = monster_time[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    
    // Step 2: BFS for the player
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int, int>>> parent_pos(n, vector<pair<int, int>>(m));
    vector<vector<char>> parent_dir(n, vector<char>(m));
    vector<vector<int>> player_time(n, vector<int>(m, INF));
    
    q.push({sr, sc});
    visited[sr][sc] = true;
    player_time[sr][sc] = 0;
    
    int end_r = -1, end_c = -1;
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
            end_r = r;
            end_c = c;
            break;
        }
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#' && !visited[nr][nc]) {
                int next_time = player_time[r][c] + 1;
                if (next_time < monster_time[nr][nc]) {
                    visited[nr][nc] = true;
                    player_time[nr][nc] = next_time;
                    parent_pos[nr][nc] = {r, c};
                    parent_dir[nr][nc] = move_char[i];
                    q.push({nr, nc});
                }
            }
        }
    }
    
    if (end_r == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        string path = "";
        int r = end_r, c = end_c;
        
        while (r != sr || c != sc) {
            path += parent_dir[r][c];
            auto [pr, pc] = parent_pos[r][c];
            r = pr; c = pc;
        }
        
        reverse(path.begin(), path.end());
        cout << path.length() << "\n";
        cout << path << "\n";
    }
    
    return 0;
}