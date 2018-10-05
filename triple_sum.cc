#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the triplets function below.
void sort_unique(const vector<int> &input, vector<int> &output) {
    set<int> unique(input.begin(), input.end());
    for (auto it = unique.begin(); it != unique.end(); ++it) {
        output.push_back(*it);
    }
}

long triplets(vector<int> a, vector<int> b, vector<int> c) {
    vector<int> sa;
    vector<int> sb;
    vector<int> sc;

    sort_unique(a, sa);
    sort_unique(b, sb);
    sort_unique(c, sc);

#if 0 // timeout
    long cnt = 0;
    unordered_map<int, long> memo;    
    for (auto n : sa) {
        for (auto it = lower_bound(sb.begin(), sb.end(), n); it != sb.end(); ++it) {
            long valid_c;

            if (memo.find(*it) == memo.end()) { // first time check this element in b.           
                auto pos = upper_bound(sc.begin(), sc.end(), *it);
                valid_c = (pos - sc.begin());
                memo[*it] = valid_c;
            } else {
                valid_c = memo[*it];
            }                        
            cnt += valid_c;
        }
    }
#else
    auto it_a = upper_bound(sa.begin(), sa.end(), sb[0]);
    long idx_a = it_a - sa.begin();
    auto it_c = upper_bound(sc.begin(), sc.end(), sb[0]);
    long idx_c = it_c - sc.begin();

    long cnt = idx_a * idx_c;    
    for (int i = 1; i < sb.size(); ++i) {
        it_a = upper_bound(it_a, sa.end(), sb[i]);
        idx_a = it_a - sa.begin();
        it_c = upper_bound(it_c, sc.end(), sb[i]);
        idx_c = it_c - sc.begin();
        cnt += idx_a * idx_c;
    }       
#endif
    return cnt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string lenaLenbLenc_temp;
    getline(cin, lenaLenbLenc_temp);

    vector<string> lenaLenbLenc = split_string(lenaLenbLenc_temp);

    int lena = stoi(lenaLenbLenc[0]);

    int lenb = stoi(lenaLenbLenc[1]);

    int lenc = stoi(lenaLenbLenc[2]);

    string arra_temp_temp;
    getline(cin, arra_temp_temp);

    vector<string> arra_temp = split_string(arra_temp_temp);

    vector<int> arra(lena);

    for (int i = 0; i < lena; i++) {
        int arra_item = stoi(arra_temp[i]);

        arra[i] = arra_item;
    }

    string arrb_temp_temp;
    getline(cin, arrb_temp_temp);

    vector<string> arrb_temp = split_string(arrb_temp_temp);

    vector<int> arrb(lenb);

    for (int i = 0; i < lenb; i++) {
        int arrb_item = stoi(arrb_temp[i]);

        arrb[i] = arrb_item;
    }

    string arrc_temp_temp;
    getline(cin, arrc_temp_temp);

    vector<string> arrc_temp = split_string(arrc_temp_temp);

    vector<int> arrc(lenc);

    for (int i = 0; i < lenc; i++) {
        int arrc_item = stoi(arrc_temp[i]);

        arrc[i] = arrc_item;
    }

    long ans = triplets(arra, arrb, arrc);

    fout << ans << "\n";

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

