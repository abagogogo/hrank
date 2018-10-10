#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the findShortest function below.

/*
 * For the unweighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] to <name>_to[i].
 *
 */
 struct Node {
    int no;
    int color;     
    vector<Node*> adj;
    bool marked;
    int depth;

    Node(int a_no, int a_color) {
        no = a_no;
        color= a_color;
        marked = false;
        depth = INT_MAX;
    }

    void connect(Node *to) {
        adj.push_back(to);
    }
 };


void do_bfs(Node *start, vector<int> &dist, int val) {
    if (start->marked) return;

    deque<Node*> q;

    start->marked = true;
    start->depth = 0;
    q.push_back(start);
    
    while (!q.empty()) {
        Node *curr = q.front(); q.pop_front();
        for (auto *next : curr->adj) {
            if (!next->marked) {
                next->marked = true;
                next->depth = curr->depth + 1;
                q.push_back(next);

                if (next->color == val) {
                    dist.push_back(next->depth);
                }
            }
        }
    }
}

int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<long> ids, int val) {
    // construct graph.
    map<int, Node *> nodes;
    for (int i = 0; i < graph_nodes; ++i) {        
        Node *n = new Node(i+1, ids[i]);
        nodes[i+1] = n;
    }
    for (int i = 0; i < graph_from.size() && i < graph_to.size(); ++i) {
        int from = graph_from[i];
        int to = graph_to[i];
        nodes[from]->connect(nodes[to]);
        nodes[to]->connect(nodes[from]);
    }
    
    // BFS
    int min_dist = INT_MAX;
    for (int id = 1; id <= nodes.size(); ++id) {
        if (nodes[id]->color != val) continue;

        vector<int> dist;
        do_bfs(nodes[id], dist, val);
        if (!dist.empty()) {
            sort(dist.begin(), dist.end());
            min_dist = min(dist[0], min_dist);
            for (int i = 1; i < dist.size(); ++i) {
                min_dist = min(dist[i] - dist[i-1], min_dist);
            }
        }
    }
    
    // TODO: free nodes allocated.
    return min_dist == INT_MAX ? -1 : min_dist;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int graph_nodes;
    int graph_edges;

    cin >> graph_nodes >> graph_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> graph_from(graph_edges);
    vector<int> graph_to(graph_edges);

    for (int i = 0; i < graph_edges; i++) {
        cin >> graph_from[i] >> graph_to[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string ids_temp_temp;
    getline(cin, ids_temp_temp);

    vector<string> ids_temp = split_string(ids_temp_temp);

    vector<long> ids(graph_nodes);

    for (int i = 0; i < graph_nodes; i++) {
        long ids_item = stol(ids_temp[i]);

        ids[i] = ids_item;
    }

    int val;
    cin >> val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int ans = findShortest(graph_nodes, graph_from, graph_to, ids, val);

    fout << ans << "\n";

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

