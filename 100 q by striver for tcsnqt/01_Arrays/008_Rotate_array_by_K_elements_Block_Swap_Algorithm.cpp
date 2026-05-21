// Problem 8: Rotate array by K elements - Block Swap Algorithm
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

void swapBlocks(vector<int>& values, int first, int second, int length) {
    for (int i = 0; i < length; i++) {
        swap(values[first + i], values[second + i]);
    }
}

void leftRotateBlockSwap(vector<int>& values, int k) {
    int n = values.size();
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    int firstBlock = k;
    int secondBlock = n - k;
    int start = 0;

    // Keep swapping the smaller block with an equal-sized part of the larger block.
    while (firstBlock != secondBlock) {
        if (firstBlock < secondBlock) {
            swapBlocks(values, start, start + secondBlock, firstBlock);
            secondBlock -= firstBlock;
        } else {
            swapBlocks(values, start, start + firstBlock, secondBlock);
            start += secondBlock;
            firstBlock -= secondBlock;
        }
    }

    swapBlocks(values, start, start + firstBlock, firstBlock);
}

int main() {
    int n, k;
    cin >> n;
    vector<int> values(n);
    for (int& value : values) cin >> value;
    cin >> k;

    leftRotateBlockSwap(values, k);
    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
