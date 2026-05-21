// Problem 17: Maximum product subarray in an array
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

long long maximumProductSubarray(const vector<int>& values) {
    // Negative numbers can turn a small negative product into a large positive product.
    long long maxEndingHere = values[0];
    long long minEndingHere = values[0];
    long long best = values[0];

    for (int i = 1; i < (int)values.size(); i++) {
        long long value = values[i];
        if (value < 0) swap(maxEndingHere, minEndingHere);

        maxEndingHere = max(value, maxEndingHere * value);
        minEndingHere = min(value, minEndingHere * value);
        best = max(best, maxEndingHere);
    }
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cout << maximumProductSubarray(values) << '\n';
    return 0;
}
