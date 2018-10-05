#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
bool match(char a, char b) {
    return (a == b) || (toupper(a) == b);
}

#if 1 // DP
string abbreviation(string a, string b) {
    int m = a.length() - 1;
    int n = b.length() - 1;    

    vector<vector<bool>> memo(m + 1, vector<bool>(n + 1, false));

    memo[m][n] = match(a[m], b[n]);
    bool remain_lower = islower(a[m]);
    for (int i = m - 1; i >= 0; --i) {
        memo[i][n] = match(a[i], b[n]) && remain_lower;
        memo[i][n] = memo[i][n] || (islower(a[i]) && memo[i+1][n]);
        remain_lower = remain_lower && islower(a[i]); 
        printf("RJ_DBG: memo[%d][n]: %s\n", i, (memo[i][n] ? "true" : "false"));
    }
    /*
    for (int j = n - 1; j >= 0; --j) {
        memo[m][j] = match(a[m], b[j]) && (memo[m][j+1] == false);
        memo[m][j] = memo[m][j] || (islower(b[j]) && memo[m][j+1]);
        printf("RJ_DBG: memo[m][%d]: %s\n", j, (memo[m][j] ? "true" : "false"));
    }
    */
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            memo[i][j] = match(a[i], b[j]) && memo[i+1][j+1];
            memo[i][j] = memo[i][j] || (islower(a[i]) && memo[i+1][j]);
            printf("RJ_DBG: memo[%d][%d]: %s\n", i, j, (memo[i][j] ? "true" : "false"));
        }
    }
    printf("memo[0][0]: %s\n", (memo[0][0] ? "YES" : "NO"));
    return (memo[0][0] ? "YES" : "NO");
}
#else // Timeout
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

