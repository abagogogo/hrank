#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int>> queries) {
    unordered_map<int, int> val_map;
    unordered_map<int, int> freq_map;
    int val, old_freq, new_freq;
    vector<int> res_list;

    for (auto q : queries) {
        val = q[1];
        switch (q[0]) {
        case 1: // add
            old_freq = val_map[val];
            val_map[val]++;
            new_freq = val_map[val];
            if (old_freq > 0) {
                freq_map[old_freq]--;
                if (freq_map[old_freq] == 0) freq_map.erase(old_freq);
            }
            freq_map[new_freq]++;
            break;

        case 2: // delete
            if (val_map.find(val) == val_map.end()) break;            
            old_freq = val_map[val];            
            val_map[val]--;
            new_freq = val_map[val];
            freq_map[old_freq]--;
            if (freq_map[old_freq] == 0) freq_map.erase(old_freq);
            if (new_freq > 0) freq_map[new_freq]++;
            else val_map.erase(val);
            break;

        case 3: // check freq
            if (freq_map.find(val) != freq_map.end()) {
                assert(freq_map[val] > 0);
                res_list.push_back(1);
            } else {
                res_list.push_back(0);
            }
            break;
        }
    }
    return res_list;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> ans = freqQuery(queries);

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

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

