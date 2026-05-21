// Problem 9: Average of all elements in an array
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

double average(const vector<int>& values) {
    long long sum = 0;
    for (int value : values) sum += value;
    return (double)sum / values.size();
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    if (values.empty()) {
        cout << "Array is empty\n";
    } else {
        cout << fixed << setprecision(2) << average(values) << '\n';
    }
    return 0;
}
