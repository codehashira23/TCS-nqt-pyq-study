/*
   TCS NQT PYQ 02: Count Subsets with Given Sum
   Source: Verified PYQ
   Difficulty: Hard
   Topics: Array, Dynamic Programming, Combinatorics

   QUESTION
   Given an array of integers and a target sum S, count all subsets of the array whose elements sum equals S, and print the answer modulo 10^9+7.

   CONSTRAINTS
   - 1 <= N <= 1000 for DP/backtracking style inputs; use modulo where asked.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   N followed by N array elements. Extra values such as K/S are read after the array when needed.

   OUTPUT FORMAT
   The answer required by the question.

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

const long long MOD=1000000007LL;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,s; cin>>n; vector<int>a(n); for(int &x:a) cin>>x; cin>>s;
    vector<long long> dp(s+1); dp[0]=1;
    for(int x:a) for(int sum=s; sum>=x; --sum) dp[sum]=(dp[sum]+dp[sum-x])%MOD;
    cout<<dp[s]<<"\n";
}
