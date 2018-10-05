#include <bits/stdc++.h>

using namespace std;

// Complete the sherlockAndAnagrams function below.
bool is_anagrams(string &s1, string &s2) {
    int freqs[26] = {0};
    
    for (auto ch : s1) freqs[ch - 'a']++;
    for (auto ch : s2) freqs[ch - 'a']--;

    for (int i = 0; i < 26; ++i)  {
        if (freqs[i] != 0) {
            printf("freqs[%d] = %d != 0 -> return false\n", i, freqs[i]);
            return false;
        }
    }
    printf("all freqs[] = 0 -> return true\n");
    return true;
}

int count_anagrams(vector<string> &list) {
    int cnt = 0;
    for (int i = 0; i < list.size()-1; ++i) {
        for (int j = i + 1; j < list.size(); ++j) {
            cout << "RJ_DBG: list[" << i << "]: " << list[i] << ", list[" << j << "]: " << list[j] << endl;
            if (is_anagrams(list[i], list[j])) cnt++;
        }
    }
    return cnt;
}

int sherlockAndAnagrams(string s) {
    int cnt = 0;
    for (int len = s.length() - 1; len >= 1; --len) {
        printf("len = %d....\n", len);
        vector<string> list;
        for (int start = 0; start + len <= s.length(); ++start) {
            list.push_back(s.substr(start, len));            
        }
        cnt += count_anagrams(list);
    }
    return cnt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

// 1
// abba
// => 4
