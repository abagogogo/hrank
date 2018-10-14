#include <bits/stdc++.h>

using namespace std;

// Complete the maxCircle function below.
struct Node {
    int id;
    int size;
    Node *parent;

    Node(int a_id) {
        id = a_id;
        size = 1;
        parent = this;
    }
};

Node *get_nodes(unordered_map<int, Node *> &nodes, int id) {
    if (nodes.find(id) == nodes.end()) {
        nodes[id] = new Node(id);
    }
    return nodes[id];
}

Node *find_set(Node *n) {
    if (n->parent == n) return n;
    Node *root = find_set(n->parent);
    if (n->parent != root) n->parent = root;
    return n->parent;
}

Node *union_set(Node *u, Node *v) {
    Node *pu = find_set(u);
    Node *pv = find_set(v);

    if (pu == pv) return pu;
    if (pu->size < pv->size) {
        Node *tmp = pu;
        pu = pv;
        pv = tmp;
    }
    pu->size += pv->size;
    pv->parent = pu;
    return pu;
}

vector<int> maxCircle(vector<vector<int>> queries) {
    unordered_map<int, Node*> nodes;
    int max_size = 0;
    vector<int> ret_list;

    for (auto q : queries) {
        Node *p = union_set(get_nodes(nodes, q[0]), 
                            get_nodes(nodes, q[1]));
        max_size = max(p->size, max_size);
        ret_list.push_back(max_size);
    }
    return ret_list;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> queries(q);
    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> ans = maxCircle(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

