#include <bits/stdc++.h>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
    vector<int> cnt(n, 1);

    for (int i = 1; i < n; ++i) {
        if (arr[i] > arr[i-1]) 
            cnt[i] = cnt[i-1] + 1;
    }
    for (int i = n - 2; i >= 0; --i) {
        if (arr[i] > arr[i+1] && cnt[i] < cnt[i+1] + 1)
            cnt[i] = cnt[i+1] + 1;
    }

    long total = 0;
    for (int i = 0; i < n; ++i) {
        cout << "arr[" << i << "]=" << arr[i] << " => " << cnt[i] << endl;
        total += cnt[i];
    }
    return total;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies(n, arr);
    cout << result << endl;

    fout << result << "\n";

    fout.close();

    return 0;
}

/*
input: 
8
2
4
3
5
2
6
4
5
output: 
12
*/

