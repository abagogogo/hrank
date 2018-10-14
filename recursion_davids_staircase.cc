#include <bits/stdc++.h>

using namespace std;

// Complete the stepPerms function below.
int stepPerms(int n) {   
#if 0
    if (n < 0) return 0;
    if (n <= 1) return 1;

     
    long cnt = (long)stepPerms(n-1) + (long)stepPerms(n-2) + (long)stepPerms(n-3);    
    return (int)(cnt % 1000000007);
#else    
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
#endif
}

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
