#if 0 // Version 1: NG
// Complete the activityNotifications function below.
int get_median_double(deque<int> &q) {
  int d = q.size();
  return (d % 2 == 1) ? (q[d / 2] * 2): (q[d / 2 - 1] + q[d / 2]);
}

void insert_q(deque<int> &q, int n) {
    q.pop_front();
    q.push_back(n);
    sort(q.begin(), q.end());
#if 0
    int start = 0;
    int end = q.size() - 1;
    int mid = 0;
    while (start < end) {
        mid = (start + end) / 2;
        if (q[mid] <= n) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    q.insert(q.begin() + mid, n);
#endif
} 

int activityNotifications(vector<int> expenditure, int d) {
    deque<int> q;
    for (int i = 0; i < d; ++i) q.push_back(expenditure[i]);
    sort(q.begin(), q.end());
    
    int cnt = 0;
    for (int i = d; i < expenditure.size(); ++i) {
        int m2 = get_median_double(q);
        if (expenditure[i] >= m2) ++cnt;
        insert_q(q, expenditure[i]);
    }
    return cnt;
}
#endif // Version 1


///////////////////

#if 0 // Version 2: Timeout
// Complete the activityNotifications function below.
int partition(vector<int> &arr, int left, int right) {
    if (left >= right) return left;

    int pivot = arr[right];
    int i = left - 1;
    int j = left;
    for (j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i;
}

int get_ith(vector<int> &arr, int left, int right, int ith) {
    int idx = partition(arr, left, right);
    int pos = idx - left;
    
    if (pos == ith) return arr[idx];
    else if (pos < ith) return get_ith(arr, left + pos + 1, right, ith - pos - 1); 
    else return get_ith(arr, left, pos - 1, ith);
}

int get_median_double(vector<int> & arr, int left, int right) {
    int d = (right - left) + 1;
    if (d % 2 == 1) {
        return get_ith(arr, left, right, d / 2) * 2;        
    } else {
        return get_ith(arr, left, right, d / 2 - 1) 
             + get_ith(arr, left, right, d / 2); 
    }
}

int activityNotifications(vector<int> expenditure, int d) {    
    int cnt = 0;
    int left = 0;
    int right = d -1;
    for (int i = d; i < expenditure.size(); ++i) {
        int m2 = get_median_double(expenditure, left, right);
        if (expenditure[i] >= m2) ++cnt;
        ++left;
        ++right;
    }
    return cnt;
}
#endif // Version 2


#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the activityNotifications function below.
int get_m2(vector<int> & freq, int d) {
    int m1 = (d + 1) / 2;
    int m2 = m1 + 1;
    int i;

    for (i = 0; i < freq.size(); ++i) {
        if (m1 <= freq[i]) {
            break;
        } else {
            m1 -= freq[i];
            m2 -= freq[i];
        }
    }
    if (d % 2 == 1) return i * 2;        

    int last_i = i;
    for (; i < freq.size(); ++i) {
        if (m2 <= freq[i]) break;
        else m2 -= freq[i]; 
    }
    return last_i + i;
}

int activityNotifications(vector<int> arr, int d) {    
    vector<int> freq(201, 0);
    int num_notification = 0;

    for (int i = 0; i < d; ++i) ++freq[arr[i]];
    for (int i = d; i < arr.size(); ++i) {
        int m2 = get_m2(freq, d);
        if (arr[i] >= m2) num_notification++;
        --freq[arr[i-d]];
        ++freq[arr[i]];
    }
    return num_notification;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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

