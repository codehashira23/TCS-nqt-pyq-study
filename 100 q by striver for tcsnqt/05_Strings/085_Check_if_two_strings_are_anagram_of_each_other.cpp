// Problem 85: Check if two strings are anagram of each other
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

bool areAnagrams(string first, string second) {
    if (first.size() != second.size()) return false;
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    return first == second;
}

int main() {
    string first, second;
    getline(cin, first);
    getline(cin, second);
    cout << (areAnagrams(first, second) ? "Yes" : "No") << '\n';
    return 0;
}
