#include <bits/stdc++.h>

using namespace std;

// Complete the stepPerms function below.
#if 1 // DP solution   
int stepPerms(int n) {   
    if (n < 0) return 0;
    if (n == 0 || n== 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 4;

    long fm3 = 1;
    long fm2 = 1;
    long fm1 = 2;
    long fm0 = 4;
    for (int i = 3; i < n; ++i) {
        fm3 = fm2;
        fm2 = fm1;
        fm1 = fm0;        
        fm0 = (fm3 + fm2 + fm1) % (long)10000000007;        
    }
    printf("DBG: n=%d => %d ways\n", n, (int)fm0);
    return (int)fm0;
}
#else // memoization solution
int helper(unordered_map<int,int> &memo, int n) {
    if (n < 0) return 0;    
    if (memo.find(n) == memo.end()) {        
        memo[n] = helper(memo, n-3) + helper(memo, n-2) + helper(memo, n-1);
    }
    return memo[n];
}
int stepPerms(int n) {
    unordered_map<int,int> memo;
    memo[0] = 0;
    memo[1] = 1;
    memo[2] = 2;
    memo[3] = 4;
    return helper(memo, n);
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int s_itr = 0; s_itr < s; s_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int res = stepPerms(n);

        fout << res << "\n";
    }

    fout.close();

    return 0;
}
