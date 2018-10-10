#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the balancedForest function below.
#if 0 // My solution
struct Node {
    int id;
    int val;
    int sum;
    //vector<Node *> children;
    Node *parent;

    Node(void) {
        id = -1;
        val = sum = 0;
        parent = nullptr;
    }

    void init(int a_id, int a_val) {
        id = a_id;
        val = sum = a_val;
    }
    void add_child(Node *child) {
        child->parent = this;
        //children.push_back(child);
        add_sum(child->sum);
    }
    void add_sum(int a_val) {
        sum += a_val;
        if (parent) parent->add_sum(a_val);
    }
    bool is_offspring(Node *p) {
        Node *curr = parent;
        while (curr) {
            if (curr == p) return true;
            curr = curr->parent;
        }
        return false;
    }
};

int balancedForest(vector<int> c, vector<vector<int>> edges) {
    if (c.size() < 3 || edges.size() < 2) return -1;

    Node g[c.size() + 1]; // 1 base.
    for (int i = 0; i < c.size(); ++i) {
        g[i + 1].init(i + 1, c[i]);
    }
    for (auto edge : edges) {
        g[edge[0]].add_child(&g[edge[1]]);
    }
    Node *root = nullptr;
    for (int i = 1; i <= c.size(); ++i) {
        if (g[i].parent == nullptr) {
            root = &g[i];
            break;
        }
    }
    assert(root);

    int min_val = INT_MAX;
    for (int i = 0; i < edges.size() - 1; ++i) {
        for (int j = i + 1; j < edges.size(); ++j) {
            Node *i0 = &g[edges[i][0]];
            Node *i1 = &g[edges[i][1]];
            Node *j0 = &g[edges[j][0]];
            Node *j1 = &g[edges[j][1]];

            int r_sum, i_sum, j_sum;
            if (j1->is_offspring(i1)) {
                r_sum = root->sum - i1->sum;
                j_sum = j1->sum;
                i_sum = i1->sum - j_sum;
            } else if (i1->is_offspring(j1)) {
                r_sum = root->sum - j1->sum;
                i_sum = i1->sum;
                j_sum = j1->sum - i_sum;
            } else {
                j_sum = j1->sum;
                i_sum = i1->sum;
                r_sum = root->sum - i_sum - j_sum;
            }
            
            // calcuate new node val.
            if (r_sum == i_sum && i_sum > j_sum) {
                min_val = min(i_sum - j_sum, min_val);
            } else if (r_sum == j_sum && j_sum > i_sum) {
                min_val = min(j_sum - i_sum, min_val);
            } else if (i_sum == j_sum && j_sum > r_sum) {
                min_val = min(j_sum - r_sum, min_val);
            }
        }
    }
    return (min_val == INT_MAX) ? -1 : min_val;
}
#else
struct Node {
    int id;
    int val;
    vector<Node *> adj;
    Node *parent;

    Node(void) {
        id = -1;
        val = 0;
        parent = nullptr;
    }

    void init(int a_id, int a_val) {
        id = a_id;
        val = a_val;
    }

    void add_neighbor(Node *n) {
        adj.push_back(n);
    }

    void dfs_sum(vector<long> &sum) {
        sum[id] = val;
        //printf("DBG: visiting id=%d, sum=%d\n", id, sum[id]);
        for (auto p : adj) {
            if (sum[p->id] == 0) {
                //printf("DBG: from id=%d to p->id=%d\n", id, p->id);
                p->parent = this;
                p->dfs_sum(sum);
                sum[id] += sum[p->id];
            }
        }
    }

    bool is_offspring(Node *p) {
        Node *curr = parent;
        while (curr) {
            if (curr == p) return true;
            curr = curr->parent;
        }
        return false;
    }
};

int balancedForest(vector<int> c, vector<vector<int>> edges) {
    if (c.size() < 3 || edges.size() < 2) return -1;

    // Construct the graph.
    vector<Node> g(c.size() + 1, Node()); // 1 base.
    for (int i = 0; i < c.size(); ++i) {
        g[i + 1].init(i + 1, c[i]);
    }
    for (auto edge : edges) {
        g[edge[0]].add_neighbor(&g[edge[1]]);
        g[edge[1]].add_neighbor(&g[edge[0]]);
    }

    // DFS to calcuate sum.
    Node *root = &g[1];
    vector<long> sum(g.size(), 0);
    root->dfs_sum(sum);
    //for (int i = 0; i < sum.size(); ++i) printf("DBG: sum[%d] = %d\n", i, sum[i]);

    // Iterate 2 edges combinations
    int min_val = INT_MAX;
    for (int i = 0; i < edges.size(); ++i) {
        Node *i0 = (g[edges[i][0]].parent != &g[edges[i][1]]) ? &g[edges[i][0]] : &g[edges[i][1]];
        Node *i1 = i0->id == edges[i][0] ? &g[edges[i][1]] : &g[edges[i][0]];

        if ((sum[i1->id] * 2 )== sum[root->id]) return 0;

        for (int j = i + 1; j < edges.size(); ++j) {
            Node *j0 = (g[edges[j][0]].parent != &g[edges[j][1]]) ? &g[edges[j][0]] : &g[edges[j][1]];
            Node *j1 = j0->id == edges[j][0] ? &g[edges[j][1]] : &g[edges[j][0]];

            int r_sum, i_sum, j_sum;
            if (j1->is_offspring(i1)) {
                r_sum = sum[root->id] - sum[i1->id];
                j_sum = sum[j1->id];
                i_sum = sum[i1->id] - j_sum;
                // printf("DBG: case 1 j1(%d) is offspring of i1(%d)\n", j1->id, i1->id);
            } else if (i1->is_offspring(j1)) {
                r_sum = sum[root->id] - sum[j1->id];
                i_sum = sum[i1->id];
                j_sum = sum[j1->id] - i_sum;
                // printf("DBG: case 2 i1(%d) is offspring of j1(%d)\n", i1->id, j1->id);
            } else {
                i_sum = sum[i1->id];
                j_sum = sum[j1->id];
                r_sum = sum[root->id] - i_sum - j_sum;
                // printf("DBG: case 3 i1(%d), i1(%d)\n", i1->id, j1->id);
            }
            // printf("DBG: r_sum=%d, i_sum=%d, j_sum=%d\n", r_sum, i_sum, j_sum);

            // calcuate new node val.
            if (r_sum == i_sum && i_sum >= j_sum) {
                min_val = min(i_sum - j_sum, min_val);
            } else if (r_sum == j_sum && j_sum >= i_sum) {
                min_val = min(j_sum - i_sum, min_val);
            } else if (i_sum == j_sum && j_sum >= r_sum) {
                min_val = min(j_sum - r_sum, min_val);
            }
        }
    }
    //printf("DBG: min_val=%d\n", min_val);
    return (min_val == INT_MAX) ? -1 : min_val;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string c_temp_temp;
        getline(cin, c_temp_temp);

        vector<string> c_temp = split_string(c_temp_temp);

        vector<int> c(n);

        for (int i = 0; i < n; i++) {
            int c_item = stoi(c_temp[i]);

            c[i] = c_item;
        }

        vector<vector<int>> edges(n - 1);
        for (int i = 0; i < n - 1; i++) {
            edges[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> edges[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = balancedForest(c, edges);

        fout << result << "\n";
    }

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

