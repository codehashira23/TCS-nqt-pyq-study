// Problem 86: Count common sub-sequence in two strings
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

long long countCommonSubsequences(const string& first, const string& second) {
    int n = first.size(), m = second.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (first[i - 1] == second[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j] + dp[i][j - 1];
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

int main() {
    string first, second;
    getline(cin, first);
    getline(cin, second);
    cout << countCommonSubsequences(first, second) << '\n';
    return 0;
}
