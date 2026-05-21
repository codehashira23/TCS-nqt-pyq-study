// Problem 25: Check if Array is a subset of another array or not
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

bool isSubset(const vector<int>& mainArray, const vector<int>& candidate) {
    unordered_map<int, int> frequency;
    for (int value : mainArray) frequency[value]++;

    for (int value : candidate) {
        if (frequency[value] == 0) return false;
        frequency[value]--;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n;
    vector<int> mainArray(n);
    for (int& value : mainArray) cin >> value;
    cin >> m;
    vector<int> candidate(m);
    for (int& value : candidate) cin >> value;

    cout << (isSubset(mainArray, candidate) ? "Yes" : "No") << '\n';
    return 0;
}
