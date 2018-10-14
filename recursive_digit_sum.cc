#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the superDigit function below.
int to_digit(string n, unordered_map<string, int> &memo) {
    if (n.length() == 1) return (n[0] - '0');
    if (memo.find(n) != memo.end()) return memo[n];

    int val = 0;
    for (auto ch : n) {
        val += (ch - '0');
    }
    memo[n] = to_digit(to_string(val), memo);
    return memo[n];
}

int superDigit(string n, int k) {
    unordered_map<string, int> memo;

    int val = to_digit(n, memo);
    int sum = 0;    
    int upper_bound = INT_MAX >> 1;
    while (k != 0) {                
        if (k & 0x1 == 0x1) {
            sum = to_digit(to_string(sum + val), memo);
        }
        if (val < upper_bound) {
            val = val << 1;            
        } else {
            val = to_digit(to_string(val << 1), memo);
        }        
        k = k >> 1;
    }          
    return sum;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    string n = nk[0];

    int k = stoi(nk[1]);

    int result = superDigit(n, k);

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

