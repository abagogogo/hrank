#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the swapNodes function below.
 */
struct Node {
    int id;
    Node *left;
    Node *right;
    int depth;

    Node(int a_id) {
        id = a_id;
        left = right = nullptr;
        depth = 1;
    }

    void add_left(Node *n) {
        left = n;
        left->depth = this->depth + 1;
    }

    void add_right(Node *n) {
        right = n;
        right->depth = this->depth + 1;
    }
};

Node *get_node(unordered_map<int, Node*> &nodes, int id) {
    if (nodes.find(id) == nodes.end()) {
        nodes[id] = new Node(id);
    }
    return nodes[id];
}

void swap_at_depth(unordered_map<int, vector<Node*>> &depth_map, int k) {
    vector<Node*> &list = depth_map[k];
    for (auto n : list) {
        Node *tmp = n->right;
        n->right = n->left;
        n->left = tmp;
    }
}

void print(Node *n, vector<int> &seq) {
    if (!n) return;
    print(n->left, seq);
    seq.push_back(n->id);
    print(n->right, seq);
}

void build_tree(
        vector<vector<int>> &indexes, 
        unordered_map<int, Node*> &nodes, 
        unordered_map<int, vector<Node*>> &depth_map) {

    for (int i = 0; i < indexes.size(); ++i) {
        int curr_id = i + 1;
        int left_id = indexes[i][0];
        int right_id = indexes[i][1];

        Node *curr = get_node(nodes, curr_id);
        if (left_id != -1) {
            curr->add_left(get_node(nodes, left_id));
        }
        if (right_id != -1) {
            curr->add_right(get_node(nodes, right_id));
        }
    }

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node *n = it->second;
        if (n) {
            depth_map[n->depth].push_back(n);
        }
    }
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    /*
     * Write your code here.
     */
    unordered_map<int, Node*> nodes;
    unordered_map<int, vector<Node*>> depth_map;
    build_tree(indexes, nodes, depth_map);

    vector<vector<int>> output;
    for (auto k : queries) {
        swap_at_depth(depth_map, k);

        vector<int> seq;
        print(nodes[1], seq);
        output.push_back(seq);
    }
    return output;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++) {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++) {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++) {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++) {
            fout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1) {
                fout << " ";
            }
        }

        if (result_row_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

/*
17
2 3
4 5
6 -1
-1 7
8 9
10 11
12 13
-1 14
-1 -1
15 -1
16 17
-1 -1
-1 -1
-1 -1
-1 -1
-1 -1
-1 -1
2
2
3 
 */
