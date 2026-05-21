/*
   TCS NQT PYQ 05: Book Exchange — Derangement Count
   Source: Verified PYQ
   Difficulty: Hard
   Topics: Mathematics, Dynamic Programming, Combinatorics

   QUESTION
   A teacher distributes N books to N students and wants to exchange them weekly so that every student gets a different book (not their own). Find the total number of valid exchanges (derangements) modulo 10^7+7.

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

const long long MOD=10000007LL;
int main(){int n; cin>>n; vector<long long>d(max(2,n+1)); d[0]=1; d[1]=0;
    for(int i=2;i<=n;i++) d[i]=((i-1)*(d[i-1]+d[i-2]))%MOD;
    cout<<d[n]<<"\n";
}
