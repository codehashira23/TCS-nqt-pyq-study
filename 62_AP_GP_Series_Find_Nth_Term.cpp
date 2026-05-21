/*
   TCS NQT PYQ 62: AP/GP Series: Find Nth Term
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Math

   QUESTION
   Given first term A, common difference D (for AP) or common ratio R (for GP), and N, compute the Nth term of either an AP or a GP series based on the given type.

   CONSTRAINTS
   - Values fit in signed 64-bit integers unless stated otherwise.
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

int main(){string type; long long a,d,n; cin>>type>>a>>d>>n; if(type=="AP") cout<<a+(n-1)*d<<"\n"; else {long long ans=a; for(int i=1;i<n;i++) ans*=d; cout<<ans<<"\n";}}
