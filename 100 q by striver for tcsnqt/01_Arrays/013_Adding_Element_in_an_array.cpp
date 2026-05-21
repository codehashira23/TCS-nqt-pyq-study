// Problem 13: Adding Element in an array
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

void insertAtPosition(vector<int>& values, int position, int element) {
    // position is 0-based. insert handles shifting internally.
    if (position < 0 || position > (int)values.size()) {
        cout << "Invalid position\n";
        return;
    }
    values.insert(values.begin() + position, element);
}

int main() {
    int n, position, element;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cin >> position >> element;

    insertAtPosition(values, position, element);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
