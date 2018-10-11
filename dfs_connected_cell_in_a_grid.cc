#include <bits/stdc++.h>

using namespace std;

// Complete the maxRegion function below.
int dfs(int r, int c, vector<vector<int>> &grid, vector<vector<bool>> &visited) {
    if (visited[r][c]) return 0;
    
    visited[r][c] = true;
    if (grid[r][c] == 0) return 0;
    int cnt = 1;
    
    for (int dr = -1; dr <= 1; ++dr) {
        int next_r = r + dr;
        if (next_r < 0 || next_r >= grid.size()) continue;

        for (int dc = -1; dc <= 1; ++dc) {
            int next_c = c + dc;
            if (next_c < 0 || next_c >= grid[0].size()) continue;
            if (next_r == r && next_c == c) continue;

            cnt += dfs(next_r, next_c, grid, visited);
        }
    }
    return cnt;
}

int maxRegion(vector<vector<int>> grid) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int max_region = 0;
    
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            int region = dfs(r, c, grid, visited);
            max_region = max(region, max_region);
        }
    }
    return max_region;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int res = maxRegion(grid);

    fout << res << "\n";

    fout.close();

    return 0;
}

