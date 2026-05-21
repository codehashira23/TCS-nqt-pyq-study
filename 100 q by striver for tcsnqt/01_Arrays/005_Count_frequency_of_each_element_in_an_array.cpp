// Problem 5: Count frequency of each element in an array
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

map<int, int> countFrequencies(const vector<int>& values) {
    // map keeps the output sorted by element.
    map<int, int> frequency;
    for (int value : values) {
        frequency[value]++;
    }
    return frequency;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;

    map<int, int> frequency = countFrequencies(values);
    for (const auto& entry : frequency) {
        cout << entry.first << " -> " << entry.second << '\n';
    }
    return 0;
}
