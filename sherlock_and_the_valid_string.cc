#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
string isValid(string str) {
    map<char, int> freqs;   
    for (char ch : str) freqs[ch]++;
    
    map<int, int> s;
    for (auto it = freqs.begin(); it != freqs.end(); ++it) {
        s[it->second]++;
    }
    if (s.size() > 2) return "NO";
    if (s.size() <= 1) return "YES"; 

    int min_freq = s.begin()->first;
    int min_cnt  = s.begin()->second;    
    int max_freq = s.rbegin()->first;
    int max_cnt  = s.rbegin()->second;

    if (((max_freq - min_freq == 1) && max_cnt == 1) || 
        (min_freq == 1 && min_cnt == 1)) {
        return "YES";
    } else {
        return "NO";
    }    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}

