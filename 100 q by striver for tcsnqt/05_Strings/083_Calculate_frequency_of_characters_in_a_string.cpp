// Problem 83: Calculate frequency of characters in a string
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
    map<char, int> frequency;
    for (char ch : text) frequency[ch]++;
    for (const auto& entry : frequency) {
        cout << entry.first << " -> " << entry.second << '\n';
    }
    return 0;
}
