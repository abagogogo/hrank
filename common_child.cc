#include <bits/stdc++.h>

using namespace std;

uint64_t g_num_cmp = 0;
uint64_t g_num_rec = 0;

// Complete the commonChild function below.
#if 0 // memoization: timeout, recursion time is closed to DP, but find_char() took too many time.
int find_char(string &str, char target, int from) { // This is the bottle neck of comparision.
    for (int i = from; i < str.length(); ++i) {
        ++g_num_cmp;
        if (str[i] == target) return i;
    }
    return str.length();
}

int childs(string &shorter, string &longer, int idx_s, int idx_l, map<char, int> &freqs_l, map<string, int> &memo) {    
    ++g_num_rec;
    if (idx_s >= shorter.length() || idx_l >= longer.length()) return 0;

    string key = to_string(idx_s) + "," + to_string(idx_l);
    if (memo[key] > 0) return memo[key];

    char ch = shorter[idx_s];
    if (freqs_l[ch] == 0) return childs(shorter, longer, idx_s+1, idx_l, freqs_l, memo);

    // with ch.
    int with_cnt = 0;
    int ch_idx = find_char(longer, ch, idx_l);
    if (ch_idx < longer.length()) {
        with_cnt = 1 + childs(shorter, longer, idx_s+1, ch_idx+1, freqs_l, memo);
    }

    int without_cnt = childs(shorter, longer, idx_s+1, idx_l, freqs_l, memo);
    memo[key] = max(with_cnt, without_cnt);
    return memo[key];
}

int commonChild(string s1, string s2) {
    string &shorter = (s1.length() <= s2.length()) ? s1 : s2;
    string &longer = (s1.length() > s2.length()) ? s1 : s2;
    
    // build frequency
    map<char, int> freqs_l;
    for (auto ch : longer) freqs_l[ch]++;

    map<string, int> memo;
    return childs(shorter, longer, 0, 0, freqs_l, memo);
}
#else // DP
int commonChild(string s1, string s2) {
    if (s1.length() == 0 || s2.length() == 0) return 0;

    vector<vector<int>> memo(s1.length(), vector<int>(s2.length(), 0));

    int m = s1.length() - 1; 
    int n = s2.length() - 1; 
    //printf("RJ_DBG: m=%d, n=%d\n", m, n);
    
    ++g_num_cmp;
    if (s1[m] == s2[n]) memo[m][n] = 1;
    //printf("RJ_DBG: memo[m][n]=%d\n", memo[m][n]);
    for (int i = m-1; i >= 0; --i) {
        ++g_num_cmp;
        if (s1[i] == s2[n]) memo[i][n] = 1;
        else memo[i][n] = memo[i+1][n];
        //printf("RJ_DBG: memo[%d][n]=%d\n", i, memo[i][n]);
    }
    for (int j = n-1; j >= 0; --j) {
        ++g_num_cmp;
        if (s1[m] == s2[j]) memo[m][j] = 1;
        else memo[m][j] = memo[m][j+1];
        //printf("RJ_DBG: memo[m][%d]=%d\n", j, memo[m][j]);
    }

    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            ++g_num_cmp;
            if (s1[i] == s2[j]) {
                memo[i][j] = memo[i+1][j+1] + 1;
                //printf("RJ_DBG: case equal -> memo[%d][%d]=%d + 1\n", i, j, memo[i+1][j+1], memo[i][j]);
            }
            memo[i][j] = max(memo[i][j], memo[i][j+1]);
            memo[i][j] = max(memo[i][j], memo[i+1][j]);
            //printf("RJ_DBG: memo[%d][%d]=%d\n", i, j, memo[i][j]);
        }
    }

    printf(" memo[0][0] = %d\n", memo[0][0]);
    return memo[0][0];
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

    printf("RJ_DBG: cmp: %lld, rec: %lld\n", g_num_cmp, g_num_rec);
    return 0;
}

