// Problem 16: Find all symmetric pairs in array
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

vector<pair<int, int>> symmetricPairs(const vector<pair<int, int>>& pairsList) {
    map<int, int> firstToSecond;
    vector<pair<int, int>> result;

    for (const auto& currentPair : pairsList) {
        int first = currentPair.first;
        int second = currentPair.second;
        if (firstToSecond.count(second) && firstToSecond[second] == first) {
            result.push_back({second, first});
        } else {
            firstToSecond[first] = second;
        }
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> pairsList(n);
    for (auto& item : pairsList) cin >> item.first >> item.second;

    vector<pair<int, int>> result = symmetricPairs(pairsList);
    for (const auto& currentPair : result) {
        cout << '(' << currentPair.first << ", " << currentPair.second << ") ";
    }
    cout << '\n';
    return 0;
}
