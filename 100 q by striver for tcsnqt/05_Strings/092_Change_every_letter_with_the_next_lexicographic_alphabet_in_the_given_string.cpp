// Problem 92: Change every letter with the next lexicographic alphabet in the given string
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

char nextLetter(char ch) {
    if (ch == 'z') return 'a';
    if (ch == 'Z') return 'A';
    if (isalpha((unsigned char)ch)) return ch + 1;
    return ch;
}

int main() {
    string text;
    getline(cin, text);
    for (char& ch : text) ch = nextLetter(ch);
    cout << text << '\n';
    return 0;
}
