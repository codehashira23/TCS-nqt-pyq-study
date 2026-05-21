// Problem 70: Insertion Sort Algorithm
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

void insertionSort(vector<int>& values) {
    for (int i = 1; i < (int)values.size(); i++) {
        int key = values[i];
        int j = i - 1;
        while (j >= 0 && values[j] > key) {
            values[j + 1] = values[j];
            j--;
        }
        values[j + 1] = key;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    insertionSort(values);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
