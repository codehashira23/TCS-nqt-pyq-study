// Problem 4: Reverse a given array
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

void reverseArray(vector<int>& values) {
    int left = 0;
    int right = (int)values.size() - 1;
    while (left < right) {
        swap(values[left], values[right]);
        left++;
        right--;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;

    reverseArray(values);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
