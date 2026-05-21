/*
   TCS NQT PYQ 41: All Subarrays with Sum Equal to K
   Source: Verified PYQ
   Exam/Shift: 26 April 2024
   Difficulty: Medium
   Topics: Array, Prefix Sum

   QUESTION
   Given an array of integers and a value K, find and print all contiguous subarrays whose sum equals K. The input format uses a comma to separate the list from K.

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

int main(){int n,k; cin>>n; vector<int>a(n); for(int &x:a) cin>>x; cin>>k; bool found=false; for(int l=0;l<n;l++){long long sum=0; for(int r=l;r<n;r++){sum+=a[r]; if(sum==k){found=true; for(int i=l;i<=r;i++) cout<<a[i]<<(i==r?'\n':' ');}}} if(!found) cout<<"No subarray found\n";}
