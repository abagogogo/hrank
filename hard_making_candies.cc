#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumPasses function below.
long buy(long &m, long &w, long cnt, long p) {
    long diff = min(cnt, abs(m - w));    
    if (m < w) {
        m += diff;
    } else if (w < m) {
        w += diff;
    }
    long remained = cnt - diff;
    if (remained > 0) {
        m += remained/2;
        w += remained/2;
        if (remained % 2 == 1) m++;
    }
    
    return m * w - cnt * p;
}

#if 0 // Mine: TIMEOUT        
long minimumPasses(long m, long w, long p, long n) {
    long sum = 0;
    long days = 0;

    while (sum < n) {
        sum += m * w;
        days++;
        if (sum >= n) break;


        while (sum - p >= 0 && sum + m * w < n) {
            sum -= p;
            if (m <= w) {
                m++;
            } else {
                w++;
            }
        }
        search(m, w, sum, p, n);
        
    }
    return days;
}
#else // Editorial
typedef long long ll;
bool check(ll machines, ll workers, ll price, ll target, ll rounds) {
    if (machines >= (target+workers-1)/workers) return true;
    ll cur = machines*workers;
    rounds--;
    if (rounds == 0) return false;
    while (1) {
        ll rem = target - cur;
        ll rnds = (rem + machines*workers - 1) / (machines*workers);
        if (rnds <= rounds) return true;
        if (cur < price) {
          rem = price - cur;
          rnds = (rem + machines*workers - 1) / (machines*workers);
          rounds -= rnds;
          if (rounds < 1) return false;
          cur += rnds * machines * workers;
        }
        cur -= price;
        if (machines > workers) {
          workers++;
        } else {
          machines++;
        }
    }
    return false;
}

long minimumPasses(long m, long w, long p, long n) {
    long left = 1;
    long right = 1e12;
    while (left < right) {
        long mid = left + (right - left) / 2;
        if (check(m, w, p, n, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string mwpn_temp;
    getline(cin, mwpn_temp);

    vector<string> mwpn = split_string(mwpn_temp);

    long m = stol(mwpn[0]);

    long w = stol(mwpn[1]);

    long p = stol(mwpn[2]);

    long n = stol(mwpn[3]);

    long result = minimumPasses(m, w, p, n);

    fout << result << "\n";

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

