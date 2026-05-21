// Problem 87: Check if two strings match where one string contains wildcard characters
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

bool wildcardMatch(const string& pattern, const string& text) {
    int n = pattern.size(), m = text.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; i++) {
        if (pattern[i - 1] == '*') dp[i][0] = dp[i - 1][0];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (pattern[i - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else if (pattern[i - 1] == '?' || pattern[i - 1] == text[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

int main() {
    string pattern, text;
    getline(cin, pattern);
    getline(cin, text);
    cout << (wildcardMatch(pattern, text) ? "Yes" : "No") << '\n';
    return 0;
}
