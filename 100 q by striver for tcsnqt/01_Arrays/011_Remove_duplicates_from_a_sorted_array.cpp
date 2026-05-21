// Problem 11: Remove duplicates from a sorted array
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

int removeDuplicates(vector<int>& values) {
    if (values.empty()) return 0;

    int write = 1;
    for (int read = 1; read < (int)values.size(); read++) {
        if (values[read] != values[read - 1]) {
            values[write] = values[read];
            write++;
        }
    }
    return write; // Elements from index 0 to write - 1 are unique.
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;

    int uniqueCount = removeDuplicates(values);
    for (int i = 0; i < uniqueCount; i++) cout << values[i] << ' ';
    cout << '\n';
    return 0;
}
