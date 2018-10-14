#include <bits/stdc++.h>

using namespace std;

// Complete the crosswordPuzzle function below.
#define HORIZONTAL 0
#define VERTICAL   1

vector<vector<int>> get_pos_list(vector<string> &crossword, string word) {
    vector<vector<int>> pos_list;

    // horizontal
    for (int row = 0; row < crossword.size(); ++row) {
        for (int j = 0; j + word.length() <= crossword[0].length(); ++j) {
            int k = 0; 
            while (k < word.length()) {                
                if (crossword[row][j + k] == '-' || 
                    crossword[row][j + k] == word[k]) {
                    ++k;
                } else {
                    break;
                }
            }
            if (k == word.length()) {
                pos_list.push_back({HORIZONTAL, row, j});
            }
        }
    }

    // vertical
    for (int col = 0; col < crossword[0].length(); ++col) {
        for (int i = 0; i + word.length() <= crossword.size(); ++i) {
            int k = 0;
            while (k < word.length()) {
                if (crossword[i + k][col] == '-' || 
                    crossword[i + k][col] == word[k]) {
                    ++k;
                } else {
                    break;
                }
            }
            if (k == word.length()) {
                pos_list.push_back({VERTICAL, i, col});
            }
        }
    }
    return pos_list;
}

void fill(vector<string> &crossword, string &word, vector<int> &pos) {
    int dir = pos[0];
    int row = pos[1]; 
    int col = pos[2];
    if (dir == HORIZONTAL) { // horizontal
        for (int i = 0; i < word.length(); ++i) {
            crossword[row][col + i] = word[i];
        }    
    } else { // vertical
        for (int i = 0; i < word.length(); ++i) {
            crossword[row + i][col] = word[i];
        }
    }
}

void revert(vector<string> &crossword, string &word, vector<int> &pos) {
    int dir = pos[0];
    int row = pos[1];
    int col = pos[2];
    if (dir == HORIZONTAL) { // horizontal
        for (int i = 0; i < word.length(); ++i) {
            crossword[row][col + i] = '-';
        }    
    } else { // vertical
        for (int i = 0; i < word.length(); ++i) {
            crossword[row + i][col] = '-';
        }
    }
}

bool solve(vector<string> &crossword, vector<string>words) {        
    if (words.size() == 0) return true;

    bool ret = false;
    string word = words.back(); 
    words.pop_back();   

    vector<vector<int>> list = get_pos_list(crossword, word);
    for (auto pos : list) {
        fill(crossword, word, pos);
        ret = solve(crossword, words);
        if (ret) break;
        revert(crossword, word, pos);
    }

    words.push_back(word);
    return ret;
}

vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    // split words
    vector<string> word_list;
    int k = 0;    
    for (int i = 0; i < words.size(); ++i) {
        if (words[i] == ';') {
            word_list.push_back(words.substr(k, i - k));
            k = i + 1;
        }
    }
    if (k < words.length()) {
        word_list.push_back(words.substr(k));
    }

    // recurse on each word
    solve(crossword, word_list);
    return crossword;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
