// Problem 19: Sorting elements of an array by frequency
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

vector<int> sortByFrequency(vector<int> values) {
    unordered_map<int, int> frequency;
    for (int value : values) frequency[value]++;

    stable_sort(values.begin(), values.end(), [&](int first, int second) {
        if (frequency[first] != frequency[second]) {
            return frequency[first] > frequency[second];
        }
        return first < second;
    });
    return values;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    for (int value : sortByFrequency(values)) cout << value << ' ';
    cout << '\n';
    return 0;
}
