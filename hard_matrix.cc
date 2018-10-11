#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minTime function below.
struct Node {
    int id;
    bool machine;
    Node *parent;

    Node(int a_id) {
        id = a_id;
        machine = false;
        parent = this;
    }
};

Node *get_node(unordered_map<int, Node*> &nodes, int id) {
    if (nodes.find(id) == nodes.end()) {
        nodes[id] = new Node(id);
    }
    return nodes[id];
}

struct EdgeCmp {
    bool operator ()(const pair<int, int> &lhs, const pair<int, int> &rhs) {
        return (lhs.first >= rhs.first);
    }
};


Node *find_set(Node *n) {
    if (n->parent == n) return n;
    n->parent = find_set(n->parent);
    return n->parent;
}

void union_set(Node *u, Node *v) {
    Node *su = find_set(u);
    Node *sv = find_set(v);
    
    if (su->machine) {
        sv->parent = su;        
    } else if (sv->machine) {
        su->parent = sv;
    } else {
        sv->parent = su;
    }
}

int minTime(vector<vector<int>> &roads, vector<int> &machines) {
    unordered_map<int, Node*> nodes;
    vector<pair<int, int>> edges;

    for (int i = 0; i < roads.size(); ++i) {
        Node *u = get_node(nodes, roads[i][0]);
        Node *v = get_node(nodes, roads[i][1]);
        edges.push_back(make_pair(roads[i][2], i));
    }
    for (int i = 0; i < machines.size(); ++i) {
        int id = machines[i];
        Node *n = get_node(nodes, id);
        n->machine = true;
    }
    
    sort(edges.begin(), edges.end(), EdgeCmp());

    int result = 0;
    for (auto e : edges) {
        int i = e.second;
        Node *u = get_node(nodes, roads[i][0]);
        Node *v = get_node(nodes, roads[i][1]);
        int weight = roads[i][2];

        if (find_set(u)->machine && find_set(v)->machine) {
            result += weight;            
        } else {
            union_set(u, v);
        }
    }
    printf("DBG: result = %d\n", result);
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    vector<vector<int>> roads(n - 1);
    for (int i = 0; i < n - 1; i++) {
        roads[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> roads[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> machines(k);

    for (int i = 0; i < k; i++) {
        int machines_item;
        cin >> machines_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        machines[i] = machines_item;
    }

    int result = minTime(roads, machines);

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

