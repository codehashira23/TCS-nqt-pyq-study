// Problem 100: Reverse words in a string
// Topic: 05 Strings
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

int main() {
    string text;
    getline(cin, text);
    stringstream stream(text);
    vector<string> words;
    string word;
    while (stream >> word) words.push_back(word);
    reverse(words.begin(), words.end());
    for (int i = 0; i < (int)words.size(); i++) {
        if (i > 0) cout << ' ';
        cout << words[i];
    }
    cout << '\n';
    return 0;
}
