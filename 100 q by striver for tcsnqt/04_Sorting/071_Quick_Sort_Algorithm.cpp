// Problem 71: Quick Sort Algorithm
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

int partitionArray(vector<int>& values, int low, int high) {
    int pivot = values[high];
    int smallerBoundary = low - 1;
    for (int current = low; current < high; current++) {
        if (values[current] <= pivot) {
            smallerBoundary++;
            swap(values[smallerBoundary], values[current]);
        }
    }
    swap(values[smallerBoundary + 1], values[high]);
    return smallerBoundary + 1;
}

void quickSort(vector<int>& values, int low, int high) {
    if (low >= high) return;
    int pivotIndex = partitionArray(values, low, high);
    quickSort(values, low, pivotIndex - 1);
    quickSort(values, pivotIndex + 1, high);
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    quickSort(values, 0, n - 1);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
