#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the maxXor function below.
#if 0 // O(n * q)
int find_max_xor(vector<int> &arr, int q, unordered_map<int, int> &memo) {    
    if (memo.find(q) == memo.end()) {
        int max_val = 0;
        for (int v : arr) {
            max_val = max((v ^ q), max_val);
        }
        memo[q] = max_val;
    }
    return memo[q];
}

vector<int> maxXor(vector<int> arr, vector<int> queries) {
    // solve here
    int max_val = *max_element(arr.begin(), arr.end());
    int mask = INT_MAX;
    while (mask > 0 && (mask >> 1) >= max_val) {
        mask >>= 1;
    }

    vector<int> list;
    unordered_map<int, int> memo;
    for (int q : queries) {
        int remain = q & mask;
        int val = find_max_xor(arr, remain, memo);
        list.push_back(val + (q - remain));
    }
    return list;
}
#else // Trie: O(n + q)
#define GET_BIT(_num, _ith) (((_num) >> (_ith)) & 0x1)

struct Node {
    Node* child[2];    
    int   number;

    Node() {
        child[0] = child[1] = nullptr;
        number = -1;
    }
};

void add_num(Node *root, int n) {
    Node *curr = root;
    for (int i = 31; i >= 0; --i) {
        int bit = GET_BIT(n, i);
        if (curr->child[bit] == nullptr) {
            curr->child[bit] = new Node();
        }
        curr = curr->child[bit];
    }
    assert(curr->child[0] == nullptr && curr->child[1] == nullptr);
    curr->number = n;    
}

int find_max_xor(Node *root, int n) {
    int inv = n ^ 0x7fffffff;
    Node *curr = root;
    for (int i = 31; i >= 0; --i) {
        int bit = GET_BIT(inv, i);        
        curr = (curr->child[bit]) ? curr->child[bit] : curr->child[bit ^ 0x1];
        assert(curr != nullptr);
    }
    assert(curr->child[0] == nullptr && curr->child[1] == nullptr && curr->number != -1);
    return curr->number;
}

vector<int> maxXor(vector<int> arr, vector<int> queries) {
    // Build a bit Trie for numbers in arr[]
    Node *root = new Node();
    for (auto n : arr) {
        add_num(root, n);
    }
    
    // Find the number in the Trie which has max XOR value for each query.
    vector<int> result;
    for (auto q : queries) {
        result.push_back(find_max_xor(root, q) ^ q);
    }

    // TODO: free trie.
    return result;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(m);

    for (int i = 0; i < m; i++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[i] = queries_item;
    }

    vector<int> result = maxXor(arr, queries);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
