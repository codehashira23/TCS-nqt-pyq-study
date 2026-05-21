// Problem 91: Remove characters from first string present in the second string
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
    string first, second;
    getline(cin, first);
    getline(cin, second);
    unordered_set<char> banned(second.begin(), second.end());
    string result;
    for (char ch : first) {
        if (!banned.count(ch)) result.push_back(ch);
    }
    cout << result << '\n';
    return 0;
}
