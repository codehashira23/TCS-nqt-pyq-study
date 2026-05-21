/*
   TCS NQT PYQ 37: Minimum Coin Change
   Source: Practice
   Difficulty: Hard
   Topics: Dynamic Programming

   QUESTION
   Given a set of coin denominations and a target amount, find the minimum number of coins required to make up the amount. Assume unlimited coins of each denomination.

   CONSTRAINTS
   - 1 <= N <= 1000 for DP/backtracking style inputs; use modulo where asked.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   The integer values described in the question.

   OUTPUT FORMAT
   The computed answer.

   EXPLANATION
   Read the statement slowly and identify the core operation:
   traversal, hashing, two pointers, dynamic programming, math formula, or graph traversal.
   The implementation below keeps the code short, but the comments above should help you
   revise the problem as a self-study note before coding it again from memory.

   TEACHING NOTE
   1. Write down what one input item means.
   2. Decide which data structure stores only the information needed for the answer.
   3. Dry-run a small custom test before trusting the code.
   4. Check edge cases: minimum N, duplicates, zero values, and negative values where allowed.
*/

#include <bits/stdc++.h>
using namespace std;

int main(){int n,amt; cin>>n; vector<int> c(n); for(int &x:c) cin>>x; cin>>amt; const int INF=1e9; vector<int> dp(amt+1,INF); dp[0]=0; for(int x:c) for(int j=x;j<=amt;j++) dp[j]=min(dp[j],dp[j-x]+1); cout<<(dp[amt]>=INF?-1:dp[amt])<<"\n";}
