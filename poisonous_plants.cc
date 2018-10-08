#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the poisonousPlants function below.
#if 0 // failed
struct Node 
{
    int plantID; // we label plants from 0 to N - 1
    int daysToDie; // the days a plant needs to die, -1 means it will not die
};

int poisonousPlants(vector<int> pesticides) {
    int N = pesticides.size();

    std::stack<Node> s;
    s.push({ 0, -1 });
    int maxDaysToDie = -1; // the max days needed to die among all the plants
    
    for (int i = 1; i < N; i++) {
        // we only care about the plants whose pesticide is smaller (potential killer)
        int daysToDie = 1;
        while (!s.empty()) {
            if (pesticides[s.top().plantID] >= pesticides[i]) {
                // need to wait the front plants to die, like "1 5 4", 4 will die only after 5 died
                daysToDie = std::max(daysToDie, s.top().daysToDie + 1);
                s.pop();
            } else { // find the killer
                break;
            }
        }
        if (s.empty()) { // this means no preceding plants have less pesticide than ith plant
            daysToDie = -1;
        }
        maxDaysToDie = std::max(maxDaysToDie, daysToDie);
        s.push({ i, daysToDie });
    }
    return maxDaysToDie;
}
#else
int poisonousPlants(vector<int> p) {
    int n = p.size();
    int *killer = new int[n]; // which killed i;
    int *daycount = new int[n]; // how long i can exist
    int *killcount = new int[n]; // how many i killed
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        daycount[i] = 0;
        killcount[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && p[st.top()] >= p[i]) {
            st.pop();
        }

        if (st.empty()) {
            killer[i] = -1;
            daycount[i] = -1;
        } else {
            killer[i] = st.top();
            killcount[killer[i]]++;
            daycount[i] += killcount[killer[i]];
            daycount[st.top()]--;
            if (killer[st.top()] >= 0 && daycount[st.top()] <= 0)
                st.pop();
        }

        st.push(i);
    }

    int max = -1;
    for (int i = 0; i < n; ++i)
        if (max < killcount[i]) max = killcount[i];

    return max;
}
#endif

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = poisonousPlants(p);

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

