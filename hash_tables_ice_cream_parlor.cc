#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the whatFlavors function below.
void print_answer(int a, int b) {
    ++a;
    ++b;
    if (a < b) {
        cout << a << " " << b << endl;
    } else {
        cout << b << " " << a << endl;
    }
}

void whatFlavors(vector<int> cost, int money) {
    unordered_map<int, vector<int>> d; //[50000];

    for (int flavor = 0; flavor < cost.size(); ++flavor) {
        int price = cost[flavor];
        d[price].push_back(flavor);
    }

    for (int flavor = 0; flavor < cost.size(); ++flavor) {
        int p1 = cost[flavor];
        if (p1 >= money) continue;
        int p2 = money - p1;

        if (d.find(p2) != d.end()) {
            if (p1 != p2) {
                print_answer(flavor, d[p2][0]);
                return;
            } else if (d[p2].size() >= 2) {
                print_answer(d[p2][0], d[p2][1]);
                return;
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int money;
        cin >> money;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string cost_temp_temp;
        getline(cin, cost_temp_temp);

        vector<string> cost_temp = split_string(cost_temp_temp);

        vector<int> cost(n);

        for (int i = 0; i < n; i++) {
            int cost_item = stoi(cost_temp[i]);

            cost[i] = cost_item;
        }

        whatFlavors(cost, money);
    }

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

