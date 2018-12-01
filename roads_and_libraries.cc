#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

#if 0
// Complete the roadsAndLibraries function below.
struct Node {
    int id;
    vector<Node *> adj;
    bool visited;

    Node(int a_id) {
        id = a_id;
        visited = false;
    }
    void connect(Node *peer) {
        adj.push_back(peer);
    }
};

int dfs(Node *node) {
    if (node->visited) return 0;
    node->visited = true;

    int cnt = 1;    
    for (auto next : node->adj) {
        cnt += dfs(next);
    }
    return cnt;
}

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {    
    unordered_map<int, Node *> node_set;

    // construct the graph.
    for (int id = 1; id <= n; ++id) {        
        Node *node = new Node(id);
        node_set[id] = node;                
    }
    for (auto edge : cities) {  
        node_set[edge[0]]->connect(node_set[edge[1]]);
        node_set[edge[1]]->connect(node_set[edge[0]]);
    }
    if (c_lib <= c_road) {
        return node_set.size() * c_lib;
    }

    // find number for component and their size    
    vector<int> components;
    for (auto it = node_set.begin(); it != node_set.end(); ++it) {        
        int cnt = dfs(it->second);
        if (cnt > 0) {
            components.push_back(cnt);
        }
    }
    long cost = 0;
    for (auto cnt : components) {
        cost += (long)c_lib;
        cost += (long)c_road * (long)(cnt - 1);
    }
    return cost;
}
#else // 2018/12/01
int dfs(unordered_map<int, vector<int>> &graph, int start, unordered_set<int> &visited) {
    if (graph.find(start) == graph.end()) return 0;
    if (visited.count(start) > 0) return 0;

    visited.insert(start);
    int num_cities = 1;
    for (int next : graph[start]) {
        num_cities += dfs(graph, next, visited);
    }
    return num_cities;
}

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    unordered_set<int> visited;
    unordered_map<int,vector<int>> graph;

    for (int i = 1; i <= n; ++i) graph[i] = {};
    
    for (auto r : cities) {
        graph[r[0]].push_back(r[1]);
        graph[r[1]].push_back(r[0]);
    }

    long cost = 0;    
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        int num_cities = dfs(graph, it->first, visited);
        if (num_cities > 0) {
            if (c_lib < c_road) {
                cost += long(num_cities) * (long)c_lib;
            } else {
                cost += (long)(num_cities - 1) * (long)c_road + (long)c_lib;
            }
        }
    }
    return cost;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

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

