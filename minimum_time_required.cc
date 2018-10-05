#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minTime function below.
#if 0 // Others
long compute_time_rec(vector<long> &machines, long production_goal, long min_days, long max_days){
    if(machines.size()==1)
        return max_days;
    
    if(min_days == max_days)
        return min_days;
    
    long mid = ( min_days + max_days )/2;
    long production = 0;
    
    for(int i =0; i< machines.size();i++)
        production+=floor(mid/machines[i]);
    
    if(production >= production_goal)
        return compute_time_rec(machines,production_goal, min_days, mid);
    else
        return compute_time_rec(machines, production_goal, mid+1, max_days);
}

long minTime(vector<long> machines, long goal) {
    sort(machines.begin(), machines.end());
    return compute_time_rec(machines, goal, 1, machines.back()*goal);
}
#else // mine
long helper(vector<long> &machines, long goal, double base, long max_val) {
    double lb = (double)goal / base;

    long left = (long)lb;      
    long right = goal * max_val;

    while (left < right) {    
        long mid = (left + right) / 2;
        long sum = 0;
        for (auto d : machines)
            sum += (mid / d);

        if (sum >= goal) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

long minTime(vector<long> machines, long goal) {
    double base = 0.0;
    long max_val = 0;
    for (auto d : machines) {
        base += 1.0 / (double)d;
        max_val = max(d, max_val);
    }
    return helper(machines, goal, base, max_val);
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nGoal_temp;
    getline(cin, nGoal_temp);

    vector<string> nGoal = split_string(nGoal_temp);

    int n = stoi(nGoal[0]);

    long goal = stol(nGoal[1]);

    string machines_temp_temp;
    getline(cin, machines_temp_temp);

    vector<string> machines_temp = split_string(machines_temp_temp);

    vector<long> machines(n);

    for (int i = 0; i < n; i++) {
        long machines_item = stol(machines_temp[i]);

        machines[i] = machines_item;
    }

    long ans = minTime(machines, goal);

    fout << ans << "\n";

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

