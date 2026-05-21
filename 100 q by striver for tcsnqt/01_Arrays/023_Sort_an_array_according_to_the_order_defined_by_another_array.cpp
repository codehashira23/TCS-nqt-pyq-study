// Problem 23: Sort an array according to the order defined by another array
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

vector<int> relativeSort(const vector<int>& values, const vector<int>& order) {
    map<int, int> frequency;
    for (int value : values) frequency[value]++;

    vector<int> result;
    for (int key : order) {
        while (frequency[key] > 0) {
            result.push_back(key);
            frequency[key]--;
        }
        frequency.erase(key);
    }

    for (const auto& entry : frequency) {
        int value = entry.first;
        int count = entry.second;
        while (count--) result.push_back(value);
    }
    return result;
}

int main() {
    int n, m;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cin >> m;
    vector<int> order(m);
    for (int& value : order) cin >> value;

    for (int value : relativeSort(values, order)) cout << value << ' ';
    cout << '\n';
    return 0;
}
