// Problem 6: Rearrange array in increasing-decreasing order
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

vector<int> increasingDecreasing(vector<int> values) {
    // Sort once. First half is increasing, second half is decreasing.
    sort(values.begin(), values.end());
    int n = values.size();
    vector<int> result;

    for (int i = 0; i < n / 2; i++) result.push_back(values[i]);
    for (int i = n - 1; i >= n / 2; i--) result.push_back(values[i]);

    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;

    for (int value : increasingDecreasing(values)) cout << value << ' ';
    cout << '\n';
    return 0;
}
