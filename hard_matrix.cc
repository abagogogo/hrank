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

#if 0 // Editorial: Dynamic programming with DFS: O(n)

/* Note of the DP
(1) f[0][s]: the least cost to make the subtree rooted at node s contains 0 machine.

(2) f[1][s]: the least cost to make the subtree rooted at node s contains 1 machine.

(3) x is the least cost for node s to have all its child node v in a state that 
    either node v has no machine inside 
    or 1 machine inside and the path between s and v will be deleted.

    x = sum of sub_x[v] for all child node v,
        where sub_x[v] = min(f[0][v], f[1][v] + w[s][v])

(4) Depending on whether a machine is a node s, 
    f[i][s] can be defined as the following cases:

    Case 1, Machine is at node s:
            f[0][s] = infinite
            f[1][s] = x

    case 2, Machine is not at node s:
            f[0][s] = x
            f[1][s] = f[0][s] + least cost to reconnect with a child with a machine
                    = min(f[0][s] - sub_x[v] + f[1][v])
            where sub_x[v] = min(f[0][v], f[1][v] + w[s][v])

(5) For example, machines at node 1 and 2, and w[1][2] = 3, w[1][3] = 4.
    
    Step 1, at node 2:
        x = 0 // As node 2 has no other neighbor except for its parent node 1.
        f[0][2] = inf // One machine at node 2.
        f[1][2] = x = 0

    Step 2, at node 3:
        x = 0 // As node 3 has no other neighbor except for its parent node 1.
        f[0][3] = x = 0 // No machine at node 3.
        f[1][3] = x + 0 = 0

    Step 3, at node 1:
        x = sub_x[2] + sub_x[3]
          = min(f[0][2], f[1][2] + w[1][2]) + min(f[0][3], f[1][3] + w[1][3])
          = min(inf, 0 + 3) + min(0, 0 + 4)
          = 3 + 0 = 3
        f[0][1] = inf // It's because one machine at node 1.
        f[1][1] = x = 3

    So, to make node 1 has less one machine insdie take the cost of 3.
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define F first
#define S second
#define mp make_pair
#define eb emplace_back
const int N = 1e5+10;
ll f[2][N];
bool machine[N];
vector<pii> con[N];
const ll inf = 1e18;
void dfs(int s, int p){
	ll x = 0;
	for(auto it: con[s]){
		int v = it.F, w = it.S;
		if(v == p) continue;
		dfs(v, s);
		x += min(w + f[1][v], f[0][v]);
	}
	if(machine[s]){
		f[1][s] = x;
		f[0][s] = inf;
		return;
	}
	f[0][s] = x;
	for(auto it: con[s]){
		int v = it.F, w = it.S;
		if(v != p) f[1][s] = min(f[1][s], x + f[1][v] - min(f[1][v] + w, f[0][v]));
	}
}
int main(){
	for(int i = 0;i<N;i++) f[1][i] = f[0][i] = inf;
	int n, k, u, v, w;
	cin >> 	n >> k;
	for(int i = 0; i < n - 1; i++){
		cin >> u >> v >> w;
		con[u].eb(mp(v,w));
		con[v].eb(mp(u,w));
	}
	int rt = -1;
	for(int i  = 0; i < k; i++){
		int node;
		cin >> node;
		machine[node] = 1;
		rt = node;
	}
	dfs(rt, -1);
	cout << min(f[0][rt], f[1][rt]) << endl;
}
#endif
