// Problem 7: Calculate sum of the elements of the array
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

long long arraySum(const vector<int>& values) {
    long long sum = 0;
    for (int value : values) sum += value;
    return sum;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cout << arraySum(values) << '\n';
    return 0;
}
