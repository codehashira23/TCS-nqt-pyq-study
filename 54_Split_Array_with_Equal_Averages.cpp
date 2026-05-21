/*
   TCS NQT PYQ 54: Split Array with Equal Averages
   Source: Verified PYQ
   Difficulty: Medium
   Topics: Array, Math

   QUESTION
   Given an array of N integers, check if it can be split into two non-empty contiguous parts such that both parts have equal averages. Print "true" if possible, otherwise print "false".

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

int main(){int n; cin>>n; vector<double>a(n),pref(n+1); for(int i=0;i<n;i++){cin>>a[i]; pref[i+1]=pref[i]+a[i];} bool ok=false; for(int i=1;i<n;i++) if(fabs(pref[i]/i-(pref[n]-pref[i])/(n-i))<1e-9) ok=true; cout<<(ok?"true":"false")<<"\n";}
