// Problem 88: Return maximum occurring character in the input string
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
    vector<int> frequency(256, 0);
    for (unsigned char ch : text) frequency[ch]++;

    char best = '\0';
    int bestCount = -1;
    for (unsigned char ch : text) {
        if (frequency[ch] > bestCount) {
            bestCount = frequency[ch];
            best = ch;
        }
    }
    cout << best << '\n';
    return 0;
}
