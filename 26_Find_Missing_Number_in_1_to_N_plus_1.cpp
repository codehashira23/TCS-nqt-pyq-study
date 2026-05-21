/*
   TCS NQT PYQ 26: Find Missing Number in 1 to N+1
   Source: Practice
   Difficulty: Easy
   Topics: Array, Math

   QUESTION
   An array contains N distinct integers taken from the range 1 to N+1 with exactly one number missing. Find the missing number.

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

int main(){long long n; cin>>n; long long expected=(n+1)*(n+2)/2, sum=0,x; for(int i=0;i<n;i++){cin>>x; sum+=x;} cout<<expected-sum<<"\n";}
