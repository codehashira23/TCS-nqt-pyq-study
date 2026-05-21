// Problem 20: Rotation of elements of array- left and right
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

void reverseRange(vector<int>& values, int left, int right) {
    while (left < right) swap(values[left++], values[right--]);
}

void rotateLeft(vector<int>& values, int k) {
    int n = values.size();
    if (n == 0) return;
    k %= n;
    reverseRange(values, 0, k - 1);
    reverseRange(values, k, n - 1);
    reverseRange(values, 0, n - 1);
}

void rotateRight(vector<int>& values, int k) {
    int n = values.size();
    if (n == 0) return;
    rotateLeft(values, n - (k % n));
}

int main() {
    int n, k;
    char direction;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cin >> k >> direction; // L for left, R for right.

    if (direction == 'L') rotateLeft(values, k);
    else rotateRight(values, k);

    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
