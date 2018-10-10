#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumMoves function below.
#if 0 // Backtrace: TIMEOUT
#define DIR_CNT 4

struct Pos {
    int x;
    int y;
};

struct Move {
    Pos pos;
    int dir;
    int step;

    bool next(int max_step, Pos &new_pos) {
        static Pos table[DIR_CNT] = {
            {-1, 0},
            {0, 1},
            {1, 0},
            {0, -1}};
    
        if (step > 1) {
            step--;
        } else {
            step = max_step - 1;
            if (dir + 1 < DIR_CNT) {
                dir++;
            } else {
                return false;
            }
        }
        new_pos.x = pos.x + table[dir].x * step;
        new_pos.y = pos.y + table[dir].y * step;
        return true;
    }
};

bool is_valid(vector<string> &grid, Pos &src, Pos &dst) {
    int n = grid.size();
    
    // Check grid boundry.
    if (dst.x < 0 || dst.x >= n || dst.y < 0 || dst.y >= n) return false;

    // Check destination is open.
    if (grid[dst.x][dst.y] != '.') return false;

    // Check path inbetwen is open.
    int x_offset = dst.x - src.x;
    int y_offset = dst.y - src.y;
    if (x_offset != 0) {
        int dir = (x_offset > 0) ? 1 : -1;
        for (int x = src.x + dir; x != dst.x; x += dir) {
            if (grid[x][dst.y] != '.') return false;
        }
    } else if (y_offset != 0) {
        int dir = (y_offset > 0) ? 1 : -1;
        for (int y = src.y + dir; y != dst.y; y += dir) {
            if (grid[dst.x][y] != '.') return false;
        }
    }
    return true;
}

bool is_new_step(Pos pos, vector<Move> &s) {
    for (auto m : s) {
        if (m.pos.x == pos.x && m.pos.y == pos.y) {
            return false;
        }
    }
    return true;
}

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    vector<Move> s;
    int min_moves = INT_MAX;

    Move new_move;   
    new_move.pos.x = startX;
    new_move.pos.y = startY;
    new_move.dir = 0;
    new_move.step = grid.size();
    printf("<DBG> push pos=%d, %d, dir=%d, step=%d\n", new_move.pos.x, new_move.pos.y, new_move.dir, new_move.step);
    s.push_back(new_move);

    while (!s.empty()) {
        Move &m = s.back();

        Pos next_pos;
        if (m.next(grid.size(), next_pos)) {
            printf("<DBG> checking pos=%d, %d, dir=%d , step=%d => new_pos=%d, %d\n", m.pos.x, m.pos.y, m.dir, m.step, next_pos.x, next_pos.y);
            if (is_valid(grid, m.pos, next_pos) && is_new_step(next_pos, s)) {
                if (next_pos.x == goalX && next_pos.y == goalY) {
                    min_moves = min((int)s.size(), min_moves);
                    printf("<DBG> Valid and end => #moves=%d\n", s.size());
                    s.pop_back();
                } else {
                    new_move.pos.x = next_pos.x;
                    new_move.pos.y = next_pos.y;
                    new_move.dir = 0;
                    new_move.step = grid.size();
                    printf("<DBG> Valid and push pos=%d, %d, dir=%d, step=%d\n", new_move.pos.x, new_move.pos.y, new_move.dir, new_move.step);
                    s.push_back(new_move);
                }
            }
        } else {
            printf("<DBG> pop for all move dir=%d and step=%d have been tried. stack size=%d\n", m.dir, m.step, s.size());
            s.pop_back();
        } 
    }
    printf("<DBG> min #moves=%d\n", min_moves);
    return min_moves;
}
#else // BFS
// Complete the minimumMoves function below.
struct Pos {
    int x;
    int y;
    int src_dist;
    int dst_dist;
    bool visited;

    void init(int ax, int ay, int asrc_dist = INT_MAX, int adst_dist = INT_MAX) {
        x = ax;
        y = ay;
        src_dist = asrc_dist;
        dst_dist = adst_dist;
        visited = false;
    }

    bool is_matched(const Pos &tgt) {
        return x == tgt.x && y == tgt.y;
    }

    vector<vector<int>> get_neighbors(const vector<string> &grid) {
        const int cnt_dir = 4;
        static int dirs[cnt_dir][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int n = grid.size();
        vector<vector<int>> list;

        for (int i = 0; i < cnt_dir; ++i) {
            int dx = dirs[i][0];
            int dy = dirs[i][1];

            for (int step = 1; step < n; ++step) {
                int ax = x + dx * step;
                int ay = y + dy * step;
                if (!is_valid_pos(grid, ax, ay)) break;

                list.push_back({ax, ay});
            }
        }
        return list;
    }

    static bool is_valid_pos(const vector<string> &grid, int ax, int ay) {
        if (ax < 0 || ax >= grid.size() || ay < 0 || ay >= grid[0].size())
            return false;
        if (grid[ax][ay] != '.')
            return false;
        return true;
    }    
};

void init_map(vector<vector<Pos>> &a_map, int n) {    
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            a_map[x][y].init(x, y);
        }
    }
}

void push_to_src_q(Pos *pos, deque<Pos *> &src_q, int src_dist) {    
    pos->visited = true;
    pos->src_dist = src_dist;
    src_q.push_back(pos);
}

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    vector<vector<Pos>> a_map(grid.size(), vector<Pos>(grid.size()));
    deque<Pos *> src_q;
    
    init_map(a_map, grid.size());
    Pos *src = &a_map[startX][startY];
    src->visited = true;
    src->src_dist = 0;
    Pos *dst = &a_map[goalX][goalY];
            
    push_to_src_q(src, src_q, 0);

    while (!src_q.empty()) {
        Pos *curr = src_q.front(); src_q.pop_front();    
        vector<vector<int>> list = curr->get_neighbors(grid);
        
        for (auto p : list) {
            Pos *next = &a_map[p[0]][p[1]];
            if (!next->visited) {
                push_to_src_q(next, src_q, curr->src_dist + 1);
                if (next->is_matched(*dst)) {
                    return next->src_dist;
                }                             
            }
        }
    }
    return -1;
}
#endif // BFS

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

