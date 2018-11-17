#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
bool match(char a, char b) {
    return (a == b) || (toupper(a) == b);
}

#if 0 // DP with memoization
bool abbreviation(const string &a, const string &b, map<string, bool> &memo) {
    int m = a.length();
    int n = b.length();

    if (n == 0) {
        for (auto ch : a) if (!islower(ch)) return false;
        return true;
    }

    string key = a + "," + b;
    if (memo.find(key) != memo.end()) return memo[key];

    bool result;
    if (match(a[m-1], b[n-1])) {
        result = abbreviation(a.substr(0, m-1), b.substr(0, n-1), memo) 
              || (islower(a[m-1]) && abbreviation(a.substr(0, m-1), b, memo));
    } else {
        if (islower(a[m-1])) {
            result = abbreviation(a.substr(0, m-1), b, memo); 
        } else {
            result = false;
        }
    }
    memo[key] = result;
    return result;
}

string abbreviation(string a, string b) {
    map<string, bool> memo;
    string result = abbreviation(a, b, memo) ? "YES" : "NO";
    cout << result << endl;
    return result;
}
#else // DP - bottome up
bool is_abbrev(string &a, string &b) {
    int m = a.length();
    int n = b.length();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;
    for (int i = 0; i < m; ++i) {
        if (islower(a[i])) dp[i+1][0] = dp[i][0];        
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (match(a[i], b[j])) {
                dp[i+1][j+1] = dp[i][j] || (islower(a[i]) && dp[i][j+1]);
            } else if (islower(a[i])) {
                dp[i+1][j+1] = dp[i][j+1];
            }
        }        
    }
    return dp[m][n];
}

string abbreviation(string a, string b) {
    string result = is_abbrev(a, b) ? "YES" : "NO";
    cout << result << endl;
    return result;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

