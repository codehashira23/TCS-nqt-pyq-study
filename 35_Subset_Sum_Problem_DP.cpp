/*
   TCS NQT PYQ 35: Subset Sum Problem (DP)
   Source: Verified PYQ
   Difficulty: Hard
   Topics: Array, Dynamic Programming

   QUESTION
   Given an array of integers and a target sum S, determine if there exists a subset with sum exactly equal to S.

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

int main(){int n,s; cin>>n; vector<int>a(n); for(int &x:a) cin>>x; cin>>s; vector<char> dp(s+1); dp[0]=1; for(int x:a) for(int j=s;j>=x;j--) dp[j]|=dp[j-x]; cout<<(dp[s]?"true":"false")<<"\n";}
