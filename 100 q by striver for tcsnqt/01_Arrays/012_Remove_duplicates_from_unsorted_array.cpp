// Problem 12: Remove duplicates from unsorted array
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

vector<int> removeDuplicates(const vector<int>& values) {
    unordered_set<int> seen;
    vector<int> result;

    for (int value : values) {
        if (seen.insert(value).second) {
            result.push_back(value); // Preserve first occurrence order.
        }
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    for (int value : removeDuplicates(values)) cout << value << ' ';
    cout << '\n';
    return 0;
}
