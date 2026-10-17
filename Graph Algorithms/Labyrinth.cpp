#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<bool>> visited;
vector<vector<pair<int, int>>> parent_pos;
vector<vector<char>> parent_dir;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    grid.resize(n);
    int sr = -1, sc = -1, er = -1, ec = -1;
    
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') {
                sr = i; sc = j;
            } else if (grid[i][j] == 'B') {
                er = i; ec = j;
            }
        }
    }
    
    visited.assign(n, vector<bool>(m, false));
    parent_pos.assign(n, vector<pair<int, int>>(m, {-1, -1}));
    parent_dir.assign(n, vector<char>(m, ' '));
    
    queue<pair<int, int>> q;
    q.push({sr, sc}); 
    visited[sr][sc] = true;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char move_char[] = {'U', 'D', 'L', 'R'};
    
    bool reached = false;
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        if (r == er && c == ec) {
            reached = true;
            break;
        }
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#' && !visited[nr][nc]) {
                visited[nr][nc] = true;
                parent_pos[nr][nc] = {r, c};
                parent_dir[nr][nc] = move_char[i];
                q.push({nr, nc});
            }
        }
    }
    
    if (!reached) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        string path = "";
        int curr_r = er, curr_c = ec;
        
        while (!(curr_r == sr && curr_c == sc)) {
            path += parent_dir[curr_r][curr_c];
            auto p = parent_pos[curr_r][curr_c];
            curr_r = p.first;
            curr_c = p.second;
        }
        
        reverse(path.begin(), path.end());
        cout << path.length() << "\n";
        cout << path << "\n";
    }
    
    return 0;
}