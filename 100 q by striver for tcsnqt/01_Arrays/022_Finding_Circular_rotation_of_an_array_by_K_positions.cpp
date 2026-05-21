// Problem 22: Finding Circular rotation of an array by K positions
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

vector<int> circularRightRotation(const vector<int>& values, int k) {
    int n = values.size();
    vector<int> result(n);
    if (n == 0) return result;
    k %= n;

    for (int i = 0; i < n; i++) {
        result[(i + k) % n] = values[i];
    }
    return result;
}

int main() {
    int n, k;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cin >> k;
    for (int value : circularRightRotation(values, k)) cout << value << ' ';
    cout << '\n';
    return 0;
}
