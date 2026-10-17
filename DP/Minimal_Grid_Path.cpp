#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class LexicographicalPathSolver {
public:
    string solve(int n, const vector<string>& grid) {
        if (n == 1) return string(1, grid[0][0]);

        string result = "";
        result += grid[0][0];

        // Active set of cells on the current diagonal (r + c = d)
        vector<pair<int, int>> active = {{0, 0}};

        // Tracks visited cells to avoid pushing duplicate candidates for the next diagonal
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        // Total steps = 2 * n - 2
        for (int step = 0; step < 2 * n - 2; ++step) {
            char min_char = 'z' + 1;
            vector<pair<int, int>> next_candidates;

            // Step 1: Collect all unique reachable neighbors (Right and Down)
            for (const auto& [r, c] : active) {
                // Move Right
                if (c + 1 < n && !visited[r][c + 1]) {
                    visited[r][c + 1] = true;
                    next_candidates.push_back({r, c + 1});
                }
                // Move Down
                if (r + 1 < n && !visited[r + 1][c]) {
                    visited[r + 1][c] = true;
                    next_candidates.push_back({r + 1, c});
                }
            }

            // Step 2: Find the smallest character among all reachable neighbors on the next diagonal
            for (const auto& [r, c] : next_candidates) {
                min_char = min(min_char, grid[r][c]);
            }

            result += min_char;

            // Step 3: Keep only candidates matching 'min_char' for the next step
            vector<pair<int, int>> next_active;
            for (const auto& [r, c] : next_candidates) {
                if (grid[r][c] == min_char) {
                    next_active.push_back({r, c});
                }
            }

            active = move(next_active);
        }

        return result;
    }
};

int main() {
    // Fast I/O for CSES
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        LexicographicalPathSolver solver;
        cout << solver.solve(n, grid) << "\n";
    }

    return 0;
}