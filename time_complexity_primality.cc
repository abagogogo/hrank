#include <bits/stdc++.h>

using namespace std;

// Complete the primality function below.
string primality(int n) {
    if (n <= 1) return "Not prime";
    if (n <= 3) return "Prime";
    if (n % 2 == 0 || n % 3 == 0) return "Not prime";

    int n_sqrt = (int)sqrt((double)n);
    for (int i = 3; i <= n_sqrt + 1; i += 2) {
        if (n % i == 0) return "Not prime";
    }
    return "Prime";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int p;
    cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int p_itr = 0; p_itr < p; p_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string result = primality(n);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
