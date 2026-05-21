/*
   TCS NQT PYQ 50: Count Frequency of Each Element in Array
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Array, Hash Map

   QUESTION
   Given an array of N integers, count and print the frequency of each unique element in the order in which they first appear.

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

int main(){int n; cin>>n; vector<long long> order; unordered_map<long long,int> f; for(int i=0;i<n;i++){long long x; cin>>x; if(!f.count(x)) order.push_back(x); f[x]++;} for(long long x:order) cout<<x<<" "<<f[x]<<"\n";}
