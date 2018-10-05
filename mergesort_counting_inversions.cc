#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the countInversions function below.
long merge(vector<int> &arr, int left, int mid, int right, vector<int> &helper) {    
    long cnt = 0;
    for (int i = left; i <= right; ++i) helper[i] = arr[i];

    int l_idx = left;
    int r_idx = mid + 1;
    int curr = left;
    while (l_idx <= mid && r_idx <= right) {
        if (helper[l_idx] <= helper[r_idx]) {
            arr[curr++] = helper[l_idx++];
        } else {
            cnt += (mid - l_idx + 1);
            arr[curr++] = helper[r_idx++];
        }
    }
    while (l_idx <= mid) {
        arr[curr++] = helper[l_idx++];
    }
    return cnt;
}

long merge_sort(vector<int> &arr, int left, int right, vector<int> &helper) {
    if (left >= right) return 0;

    int mid = (left + right) / 2;
    long cnt = merge_sort(arr, left, mid, helper);
    cnt += merge_sort(arr, mid + 1, right, helper);
    cnt += merge(arr, left, mid, right, helper);
    return cnt;
}

long countInversions(vector<int> arr) {
    vector<int> helper(arr.size());
    return merge_sort(arr, 0, arr.size()-1, helper);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        long result = countInversions(arr);

        fout << result << "\n";
    }

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

