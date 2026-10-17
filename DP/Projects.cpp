#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Project {
    int start;
    int end;
    long long reward;
};

// Sort projects by ending day
bool compareProjects(const Project& p1, const Project& p2) {
    return p1.end < p2.end;
}

class ProjectsSolver {
public:
    long long maxEarnings(int n, vector<Project>& projects) {
        // Step 1: Sort projects by end day
        sort(projects.begin(), projects.end(), compareProjects);

        // Step 2: Store end days in a separate vector for simple binary search
        vector<int> end_days(n);
        for (int i = 0; i < n; i++) {
            end_days[i] = projects[i].end;
        }

        // dp[i] = max earnings considering first i sorted projects
        vector<long long> dp(n + 1, 0);

        for (int i = 0; i < n; i++) {
            // Find count of projects ending strictly before projects[i].start
            int idx = lower_bound(end_days.begin(), end_days.begin() + i, projects[i].start) - end_days.begin();

            // Option 1: Skip current project -> dp[i]
            // Option 2: Attend current project -> dp[idx] + reward
            dp[i + 1] = max(dp[i], dp[idx] + projects[i].reward);
        }

        return dp[n];
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<Project> projects(n);
        for (int i = 0; i < n; i++) {
            cin >> projects[i].start >> projects[i].end >> projects[i].reward;
        }

        ProjectsSolver solver;
        cout << solver.maxEarnings(n, projects) << "\n";
    }

    return 0;
}