// Problem 76: Remove all vowels from the string
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

bool isVowel(char ch) {
    ch = tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

string removeVowels(const string& text) {
    string result;
    for (char ch : text) {
        if (!isVowel(ch)) result.push_back(ch);
    }
    return result;
}

int main() {
    string text;
    getline(cin, text);
    cout << removeVowels(text) << '\n';
    return 0;
}
