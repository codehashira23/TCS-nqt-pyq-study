// Problem 21: Finding equilibrium index of an array
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

int equilibriumIndex(const vector<int>& values) {
    long long totalSum = 0;
    for (int value : values) totalSum += value;

    long long leftSum = 0;
    for (int i = 0; i < (int)values.size(); i++) {
        long long rightSum = totalSum - leftSum - values[i];
        if (leftSum == rightSum) return i;
        leftSum += values[i];
    }
    return -1;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cout << equilibriumIndex(values) << '\n';
    return 0;
}
