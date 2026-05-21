// Problem 3: Second Smallest and Second Largest element in an array
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

pair<int, int> secondSmallestAndLargest(const vector<int>& values) {
    // Store distinct first and second values.
    int smallest = INT_MAX, secondSmallest = INT_MAX;
    int largest = INT_MIN, secondLargest = INT_MIN;

    for (int value : values) {
        if (value < smallest) {
            secondSmallest = smallest;
            smallest = value;
        } else if (value != smallest && value < secondSmallest) {
            secondSmallest = value;
        }

        if (value > largest) {
            secondLargest = largest;
            largest = value;
        } else if (value != largest && value > secondLargest) {
            secondLargest = value;
        }
    }

    if (secondSmallest == INT_MAX || secondLargest == INT_MIN) {
        return {-1, -1}; // Not enough distinct elements.
    }
    return {secondSmallest, secondLargest};
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;

    auto answer = secondSmallestAndLargest(values);
    cout << answer.first << ' ' << answer.second << '\n';
    return 0;
}
