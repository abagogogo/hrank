#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the largestRectangle function below.
#if 0 // TIMEOUT: O(n^2)
long largestRectangle(vector<int> h) {
    int n = h.size();
    long max_area = 0;    
        
    for (int i = 0; i < n; ++i) {        
        int min_h = h[i];
        for (int j = i; j < n; ++j) {
            min_h = min(h[j], min_h);
            long area = (long)(j - i + 1) * (long)min_h;
            max_area = max(area, max_area);
        }
    }
    return max_area;
}
#else
long largestRectangle(vector<int> h) {
    long max_area = 0;
    stack<vector<int>> s; // stack of {height, left_index}

    h.push_back(0);
    s.push({h[0], 0});
    for (int i = 1; i < h.size(); ++i) {
        if (h[i] >= h[i-1]) {
            s.push({h[i], i});
        } else {
            int left_idx = i;
            while (!s.empty() && s.top()[0] >= h[i]) {
                left_idx = s.top()[1];  
                long area = s.top()[0] * (i - s.top()[1]);       
                max_area = max(area, max_area);
                s.pop();
            }
            s.push({h[i], left_idx});
        }
    }

    return max_area;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string h_temp_temp;
    getline(cin, h_temp_temp);

    vector<string> h_temp = split_string(h_temp_temp);

    vector<int> h(n);

    for (int i = 0; i < n; i++) {
        int h_item = stoi(h_temp[i]);

        h[i] = h_item;
    }

    long result = largestRectangle(h);

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

