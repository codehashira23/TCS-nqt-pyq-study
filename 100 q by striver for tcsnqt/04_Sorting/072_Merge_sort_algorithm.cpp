// Problem 72: Merge sort algorithm
// Topic: 04 Sorting
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

void mergeParts(vector<int>& values, int left, int mid, int right) {
    vector<int> merged;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (values[i] <= values[j]) merged.push_back(values[i++]);
        else merged.push_back(values[j++]);
    }
    while (i <= mid) merged.push_back(values[i++]);
    while (j <= right) merged.push_back(values[j++]);

    for (int k = 0; k < (int)merged.size(); k++) {
        values[left + k] = merged[k];
    }
}

void mergeSort(vector<int>& values, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(values, left, mid);
    mergeSort(values, mid + 1, right);
    mergeParts(values, left, mid, right);
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    mergeSort(values, 0, n - 1);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
