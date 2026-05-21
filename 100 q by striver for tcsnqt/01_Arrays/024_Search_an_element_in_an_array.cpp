// Problem 24: Search an element in an array
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

int linearSearch(const vector<int>& values, int target) {
    for (int i = 0; i < (int)values.size(); i++) {
        if (values[i] == target) return i;
    }
    return -1;
}

int main() {
    int n, target;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cin >> target;
    cout << linearSearch(values, target) << '\n';
    return 0;
}
