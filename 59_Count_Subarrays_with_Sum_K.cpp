/*
   TCS NQT PYQ 59: Count Subarrays with Sum = K
   Source: Verified PYQ
   Exam/Shift: 6 May 2024 Shift 1
   Difficulty: Medium
   Topics: Array, Hash Map, Prefix Sum

   QUESTION
   Given a sequence of integers nums and an integer K, find the total count of contiguous subarrays whose elements sum equals exactly K.

   CONSTRAINTS
   - 1 <= N <= 100000 unless the statement says a smaller limit.
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

int main(){int n,k; cin>>n; vector<int>a(n); for(int &x:a) cin>>x; cin>>k; unordered_map<long long,int> f; f[0]=1; long long sum=0,ans=0; for(int x:a){sum+=x; ans+=f[sum-k]; f[sum]++;} cout<<ans<<"\n";}
