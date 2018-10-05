#include <bits/stdc++.h>

using namespace std;

// Complete the isBalanced function below.
bool is_open(char ch) {
    return ch == '{' || ch == '[' || ch == '(';
}

bool is_matched(char open, char close) {
    if (open == '{')
        return close == '}';
    else if (open == '[')
        return close == ']';
    else if (open == '(')
        return close == ')';
    else
        return false;
}

string isBalanced(string s) {
    vector<char> opens;

    for (auto ch : s) {
        if (is_open(ch)) 
            opens.push_back(ch);
        else {
            if (!opens.empty()) {                
                if (!is_matched(opens.back(), ch)) 
                    return "NO";
                opens.pop_back();
            } else {
                return "NO";
            }
        }
    }
    return opens.empty() ? "YES" : "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string result = isBalanced(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

