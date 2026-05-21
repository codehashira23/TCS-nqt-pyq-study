/*
   TCS NQT PYQ 03: Chocolate Packets — Move Empty Packets to End
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Array, Two Pointers

   QUESTION
   A factory produces N chocolate packets. Empty (defective) packets are represented as 0. Push all empty packets (0s) to the end of the array while maintaining the relative order of non-zero packets.

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

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
    int n; cin>>n; vector<int>a(n); for(int &x:a) cin>>x;
    int pos=0; for(int x:a) if(x!=0) a[pos++]=x; while(pos<n) a[pos++]=0;
    for(int i=0;i<n;i++) cout<<a[i]<<(i+1==n?'\n':' ');
}
