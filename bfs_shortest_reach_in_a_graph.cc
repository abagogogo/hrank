#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <cassert>

using namespace std;

struct Node {
    int id;
    vector<Node *> adj;
    int depth;
    bool marked;

    Node (int a_id) {
        id = a_id;
        depth = -1;
        marked = false;
    }
};

class Graph {
    public:
        vector<Node *> nodes;

        Graph(int n) {            
            for (int i = 0; i < n; ++i) {
                nodes.push_back(new Node(i));
            }
        }
    
        void add_edge(int u, int v) {            
            nodes[u]->adj.push_back(nodes[v]);
            nodes[v]->adj.push_back(nodes[u]);
        }
    
        vector<int> shortest_reach(int start) {
            deque<Node*> q;

            nodes[start]->depth = 0;
            nodes[start]->marked = true;
            q.push_back(nodes[start]);
            while (!q.empty()) {
                Node *curr = q.front(); q.pop_front();
                for (Node *next : curr->adj) {
                    if (next->marked == false) {
                        next->depth = curr->depth + 6;
                        next->marked = true;
                        q.push_back(next);
                    }
                }
            }

            vector<int> ret;
            for (int i = 0; i < nodes.size(); ++i) {
                ret.push_back(nodes[i]->depth);
            }
            return ret;
        }
    
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
		int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
		int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
