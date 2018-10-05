#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumSwaps function below.
#if 0
int partition(vector<int> &arr, int start, int end, int &num_swaps) {
    int pivot = arr[end];

    int i = start - 1;
    for (int j = start; j < end; ++j) {
        if (arr[j] <= pivot) {
            printf("RJ_DBG: i=%d, j=%d, start=%d, end=%d, a[j]=%d, pivot=%d\n", i, j , start, end, arr[j], pivot);
            ++i;
            if (arr[i] > pivot) {
                swap(arr[i], arr[j]);
                ++num_swaps;
            }
        }
    }

    if (i + 1 != end) {
        printf("RJ_DBG: i+1=%d, end=%d pivot=%d\n", i + 1, end, pivot);
        ++num_swaps;
    }
    printf("RJ_DBG: num_swaps = %d\n",  num_swaps);
    arr[end] = arr[i + 1];
    arr[i + 1] = pivot;
    
    return (i + 1);
}

int qsort(vector<int> &arr, int start, int end) {
    int num_swaps = 0;

    if (start >= end) return 0;
    int mid = partition(arr, start, end, num_swaps);
    num_swaps += qsort(arr, start, mid - 1);
    num_swaps += qsort(arr, mid + 1, end);
    printf("RJ_DBG: return num_swaps = %d\n",  num_swaps);
    return num_swaps;
}
int minimumSwaps(vector<int> arr) {
    return qsort(arr, 0, arr.size()-1);
}
#else
int minimumSwaps(vector<int> arr) {
    int cnt = 0;
    int i = 0;
    while (i < arr.size()) {
        printf("RJ_DBG: i=%d, arr[i]=%d\n", i, arr[i]);
        if (arr[i] == i+1 || i == arr.size() -1) {
            ++i;
        } else {
            int idx = arr[i] - 1;
            printf("RJ_DBG: swaping i=%d, with idx=%d\n", i, idx);
            swap(arr[i], arr[idx]);
            printf("RJ_DBG: a[i]=%d, arr[idx]=%d\n", arr[i], arr[idx]);
            ++cnt;
        }
        if (cnt > 10) break;
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

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int res = minimumSwaps(arr);

    fout << res << "\n";

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
