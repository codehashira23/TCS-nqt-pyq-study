// Problem 69: Selection Sort Algorithm
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

void selectionSort(vector<int>& values) {
    int n = values.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (values[j] < values[minIndex]) minIndex = j;
        }
        swap(values[i], values[minIndex]);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    selectionSort(values);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
