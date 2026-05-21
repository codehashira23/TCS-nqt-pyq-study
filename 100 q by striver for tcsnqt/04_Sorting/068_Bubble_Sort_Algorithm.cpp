// Problem 68: Bubble Sort Algorithm
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

void bubbleSort(vector<int>& values) {
    int n = values.size();
    for (int pass = 0; pass < n - 1; pass++) {
        bool swapped = false;
        for (int i = 0; i < n - pass - 1; i++) {
            if (values[i] > values[i + 1]) {
                swap(values[i], values[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Already sorted.
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    bubbleSort(values);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
