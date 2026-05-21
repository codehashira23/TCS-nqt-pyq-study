/*
   TCS NQT PYQ 67: Distinct Elements in Array
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Array

   QUESTION
   Find and print all distinct elements from an array of size n (n <= 20), maintaining the order of their first occurrence.

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

int main(){int n; cin>>n; vector<long long>a(n); unordered_set<long long> seen; vector<long long> ans; for(auto &x:a){cin>>x; if(!seen.count(x)){seen.insert(x); ans.push_back(x);}} for(size_t i=0;i<ans.size();i++) cout<<ans[i]<<(i+1==ans.size()?'\n':' ');}
