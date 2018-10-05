#include <bits/stdc++.h>

using namespace std;

// Complete the makeAnagram function below.
int makeAnagram(string a, string b) {
    map<char,int> freq;
    
    for (auto ch : a) freq[ch]++;
    for (auto ch : b) freq[ch]--;
    int remained = 0;
    for (auto it = freq.begin(); it != freq.end(); ++it) {
        remained += abs(it->second);
    }
    return remained;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}
