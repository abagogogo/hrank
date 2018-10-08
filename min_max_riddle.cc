#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the riddle function below.
#if 0 // O(n^nlogn): TIMOEUT
vector<long> riddle(vector<long> arr) {
    // complete this function   
    vector<long> answer; 

    answer.push_back(*max_element(arr.begin(), arr.end()));
    for (int w = 2; w <= arr.size(); ++w) {
        // initialize max as first min in the window
        map<long, int> mh;        
        for (int i = 0; i < w; ++i) mh[arr[i]]++;            
        long a_max = mh.begin()->first; 

        for (int i = 0; i + w < arr.size(); ++i) {
            mh[arr[i]]--;
            if (mh[arr[i]] == 0) mh.erase(arr[i]);
            mh[arr[i + w]]++;
            a_max = max(mh.begin()->first, a_max);
        }

        answer.push_back(a_max);
    }
    return answer;
}
#else // O(n)
vector<long> riddle(vector<long> arr) {
    int n = arr.size();
    vector<int> left(n, -1); // index to the next element < a[i] on the left.
    vector<int> right(n, n); // index to the next element < a[i] on the right.
    stack<int> s;

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        if (!s.empty()) {
            left[i] = s.top();
        }
        s.push(i);
    }
    while (!s.empty()) s.pop();

    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        if (!s.empty()) {
            right[i] = s.top();
        }
        s.push(i);
    }

    vector<long> ans(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int window = (right[i] - 1) - (left[i] + 1) + 1;
        ans[window] = max(arr[i], ans[window]);
    }

    for (int window = n - 1; window >= 1; --window) {
        ans[window] = max(ans[window], ans[window + 1]);
    }
    ans.erase(ans.begin());
    return ans;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<long> res = riddle(arr);

    for (int i = 0; i < res.size(); i++) {
        fout << res[i];

        if (i != res.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

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
