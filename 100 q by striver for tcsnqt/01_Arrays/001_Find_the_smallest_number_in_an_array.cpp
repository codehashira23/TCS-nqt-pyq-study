// Problem 1: Find the smallest number in an array
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

int findSmallest(const vector<int>& values) {
    // The smallest element seen so far is enough information.
    int smallest = values[0];
    for (int value : values) {
        if (value < smallest) {
            smallest = value;
        }
    }
    return smallest;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;

    if (values.empty()) {
        cout << "Array is empty\n";
        return 0;
    }

    cout << findSmallest(values) << '\n';
    return 0;
}
