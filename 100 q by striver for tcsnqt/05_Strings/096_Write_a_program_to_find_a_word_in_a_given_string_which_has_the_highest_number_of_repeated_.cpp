// Problem 96: Write a program to find a word in a given string which has the highest number of repeated letters
// Topic: 05 Strings
//
// How to study this file:
// - Read the top comments first to understand the idea.
// - Then read the function, because the function is the reusable solution.
// - Finally read main(), which shows a simple input-output format.
//
// All code uses C++17 and avoids shortcuts so that the logic is easy to revise.

#include <bits/stdc++.h>
using namespace std;

int repeatedLetterCount(const string& word) {
    unordered_map<char, int> frequency;
    for (char ch : word) frequency[ch]++;
    int repeated = 0;
    for (const auto& entry : frequency) {
        if (entry.second > 1) repeated += entry.second;
    }
    return repeated;
}

int main() {
    string text;
    getline(cin, text);
    stringstream stream(text);
    string word, answer;
    int bestScore = 0;

    while (stream >> word) {
        int score = repeatedLetterCount(word);
        if (score > bestScore) {
            bestScore = score;
            answer = word;
        }
    }

    cout << (answer.empty() ? "-1" : answer) << '\n';
    return 0;
}
