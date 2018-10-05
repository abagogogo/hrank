#include <bits/stdc++.h>

using namespace std;

// Complete the substrCount function below.
#if 0 // Timeout
long substrCount(string &str, int len) {
    if (str.length() == 0 || len <= 0) return 0;

    long valid_cnt = 0;
    for (int i = 0; i + len <= str.length(); ++i) {
        bool valid = true;
        for (int j = 0; j < len; ++j) {
            if (str[i + j] != str[i]) {
                if ((len % 2 == 0) || (j != (len / 2))) {
                    printf("RJ_DBG: len=%d, i=%d, j=%d => break\n", len, i, j);
                    valid = false;
                    break;
                }
            }
        }
        if (valid) {
            ++valid_cnt;
            printf("RJ_DBG: len=%d, i=%d is valid\n", len, i);
        }
    }

    printf("RJ_DBG: len=%d valid_cnt=%d\n", len, valid_cnt);
    return valid_cnt + substrCount(str, len - 1);
}

long substrCount(int n, string s) {
    map<char,int> freqs;
    int max_freq = 0;
    for (auto ch : s) freqs[ch]++;
    for (auto it = freqs.begin(); it != freqs.end(); ++it) 
        if (it->second > max_freq) max_freq = it->second;
    
    int cnt = substrCount(s, max_freq + 1);
    printf("RJ_DBG: total count = %d\n", cnt);
    return cnt;
}
#else if 0 // O(n^2)
    static long substrCount(string s)
    {
        long retVal = s.Length;

        for (int i = 0; i < s.Length; i++)
        {
            var startChar = s[i];
            int diffCharIdx = -1;
            for (int j = i + 1; j < s.Length; j++)
            {
                var currChar = s[j];
                if (startChar == currChar)
                {
                    if ((diffCharIdx == -1) ||
                       (j - diffCharIdx) == (diffCharIdx - i))
                        retVal++;
                }
                else
                {
                    if (diffCharIdx == -1)
                        diffCharIdx = j;
                    else
                        break;
                }
            }
        }
        return retVal;
    }
#else // one parse
static long substrCount(int n, String s) {
    // initialize counter to n because each character is a
    // palindromic string
    int counter = n;
				
    // to count consecutive characters that are the same
    int consec = 1;
				
    // the middle index of a 3-character symmetry,
    // assigned only once detected
    int midIndex = -1;
				
    // compare with previous character so start with i=1
    for (int i = 1; i < n; i++) {
        if (s.charAt(i) == s.charAt(i-1)) {
            // Condition 1: All of the characters are the same
            // For n consecutive characters that are the same,
            // we have this formula:
            // Number of palindromic strings =
            //     (n-1) + (n-2) + ... + (n-(n-1))
            counter += consec;
            consec++;
                
            // Condition 2: All characters except the middle one
            // are the same
            if (midIndex > 0) {
                // check for symmetry on both sides
                // of the midIndex
                if ((midIndex-consec) > 0 && s.charAt(midIndex-consec) == s.charAt(i)) {
                    counter++;
                } else {
                    // no more possibility of palindromic string
                    // with this midIndex
                    midIndex = -1; 
                }
            }
        } else {
            // reset consecutive chars counter to 1
            consec = 1;
                
            // check for a 3-character symmetry
            if (((i-2) >= 0) && s.charAt(i-2) == s.charAt(i)) {
                counter++; // 3-char symmetry is detected
                    
                // to check if the next characters are the same
                // and symmetrical along the midIndex
                midIndex = i-1;
            } else {
                midIndex = -1;
            }
        }
    }
    return counter;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
