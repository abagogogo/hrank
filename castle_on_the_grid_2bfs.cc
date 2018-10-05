#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumMoves function below.
struct Pos {
    int x;
    int y;
    char pattern;
    int src_dist;
    int dst_dist;
    bool visited;

    void init(int a_x, int a_y, char a_pattern, int a_src_dist = INT_MAX, int a_dst_dist = INT_MAX) {
        x = a_x;
        y = a_y;
        pattern = a_pattern;
        src_dist = a_src_dist;
        dst_dist = a_dst_dist;
        visited = false;
    }

    bool is_matched(const Pos &tgt) {
        return x == tgt.x && y == tgt.y;
    }

    vector<vector<int>> get_neighbors(const vector<vector<Pos>> &a_map) {
        const int cnt_dir = 4;
        static int dirs[cnt_dir][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int n = a_map.size();

        vector<vector<int>> neighbors;
        for (int i = 0; i < cnt_dir; ++i) {
            int dx = dirs[i][0];
            int dy = dirs[i][1];

            for (int step = 1; step < n; ++step) {
                int ax = x + dx * step;
                int ay = y + dy * step;
                if (!is_valid_pos(a_map, ax, ay)) break;

                neighbors.push_back({ax, ay});
            }
        }
        return neighbors;
    }

    void push_to_src_q(deque<Pos *> &q, int src_dist) {    
        this->visited = true;
        this->src_dist = src_dist;
        q.push_back(this);
    }

    void push_to_dst_q(deque<Pos *> &q, int dst_dist) {    
        this->visited = true;
        this->dst_dist = dst_dist;
        q.push_back(this);
    }

    static bool is_valid_pos(const vector<vector<Pos>> &a_map, int ax, int ay) {
        if (ax < 0 || ax >= a_map.size() || ay < 0 || ay >= a_map[0].size())
            return false;
        if (a_map[ax][ay].pattern != '.')
            return false;
        return true;
    }    
};

void init_map(vector<vector<Pos>> &a_map, const vector<string> &grid) {
    int n = grid.size();
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            a_map[x][y].init(x, y, grid[x][y]);
        }
    }
}

int search_from_src(deque<Pos *> &src_q, Pos *dst, vector<vector<Pos>> &a_map) {    
    if (src_q.empty()) return -1;

    Pos *curr = src_q.front(); src_q.pop_front();   
    auto s_list = curr->get_neighbors(a_map);
    for (auto p : s_list) {
        Pos *next = &a_map[p[0]][p[1]];

        if (next->is_matched(*dst)) {
            return curr->src_dist + 1;
        } else if (next->dst_dist != INT_MAX) {
            return curr->src_dist + 1 + next->dst_dist;
        } else if (!next->visited) {
            next->push_to_src_q(src_q, curr->src_dist + 1);
        }            
    }
    return -1;
}

int search_from_dst(deque<Pos *> &dst_q, Pos *src, vector<vector<Pos>> &a_map) {    
    if (dst_q.empty()) return -1;

    Pos *curr = dst_q.front(); dst_q.pop_front();    
    auto d_list = curr->get_neighbors(a_map);   
    for (auto p : d_list) {
        Pos *next = &a_map[p[0]][p[1]];

        if (next->is_matched(*src)) {
            return curr->dst_dist + 1;
        } else if (next->src_dist != INT_MAX) {
            return curr->dst_dist + 1 + next->src_dist;                
        } else if (!next->visited) {
            next->push_to_dst_q(dst_q, curr->dst_dist + 1);
        }            
    }
    return -1;
}

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    vector<vector<Pos>> a_map(grid.size(), vector<Pos>(grid.size()));
    deque<Pos *> src_q, dst_q;
    
    init_map(a_map, grid);
    Pos *src = &a_map[startX][startY];
    src->push_to_src_q(src_q, 0);
    Pos *dst = &a_map[goalX][goalY];
    dst->push_to_dst_q(dst_q, 0);
    
    int result = -1;
    while (result == -1) {  
        if (!src_q.empty()) {
            result = search_from_src(src_q, dst, a_map);
        } 
        if (!dst_q.empty() && result == -1) {
            result = search_from_dst(dst_q, src, a_map);
        }
        if (src_q.empty() && dst_q.empty()) break;  
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string startXStartY_temp;
    getline(cin, startXStartY_temp);

    vector<string> startXStartY = split_string(startXStartY_temp);

    int startX = stoi(startXStartY[0]);

    int startY = stoi(startXStartY[1]);

    int goalX = stoi(startXStartY[2]);

    int goalY = stoi(startXStartY[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

