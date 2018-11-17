#include <bits/stdc++.h>

using namespace std;

// Complete the substrCount function below.
#if 0 // O(n^2)
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
#endif
#if 1 // one parse
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
#else // O(n): 2-pass, reduce and count.
long substrCount(int n, string s) {
    if (n == 0) return 0;

    long cnt = n;
    vector<char> uni_s;
    unordered_map<long, long> uni_cnt;

    uni_s.push_back(s[0]);
    uni_cnt[uni_s.size() - 1] = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i-1]) {
            cnt += uni_cnt[uni_s.size() - 1];
            uni_cnt[uni_s.size() - 1]++;            
        } else {
            uni_s.push_back(s[i]);
            uni_cnt[uni_s.size() - 1] = 1;
        }
    }

    for (int i = 1; i < uni_s.size(); ++i) {
        if (uni_cnt[i] == 1 && i + 1 < uni_s.size()) {
            if (uni_s[i - 1] == uni_s[i + 1]) {
                cnt += min(uni_cnt[i-1], uni_cnt[i+1]);
            }
        }
    }
    return cnt;
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
