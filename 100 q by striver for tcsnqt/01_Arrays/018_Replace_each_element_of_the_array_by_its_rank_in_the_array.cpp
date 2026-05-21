// Problem 18: Replace each element of the array by its rank in the array
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

vector<int> replaceByRank(const vector<int>& values) {
    vector<int> sorted = values;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    unordered_map<int, int> rank;
    for (int i = 0; i < (int)sorted.size(); i++) {
        rank[sorted[i]] = i + 1;
    }

    vector<int> result;
    for (int value : values) result.push_back(rank[value]);
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    for (int value : replaceByRank(values)) cout << value << ' ';
    cout << '\n';
    return 0;
}
