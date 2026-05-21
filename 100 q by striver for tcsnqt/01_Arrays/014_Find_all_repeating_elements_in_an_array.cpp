// Problem 14: Find all repeating elements in an array
// Topic: 01 Arrays
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

vector<int> repeatingElements(const vector<int>& values) {
    map<int, int> frequency;
    for (int value : values) frequency[value]++;

    vector<int> result;
    for (const auto& entry : frequency) {
        if (entry.second > 1) result.push_back(entry.first);
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    for (int value : repeatingElements(values)) cout << value << ' ';
    cout << '\n';
    return 0;
}
