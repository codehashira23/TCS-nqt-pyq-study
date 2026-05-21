/*
   TCS NQT PYQ 47: Matrix Addition
   Source: Verified PYQ
   Difficulty: Easy
   Topics: Matrix

   QUESTION
   Given two N x M matrices A and B of the same size, compute their sum matrix C where C[i][j] = A[i][j] + B[i][j].

   CONSTRAINTS
   - Values fit in signed 64-bit integers unless stated otherwise.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   N M, then N*M integers of matrix A, then N*M integers of matrix B.

   OUTPUT FORMAT
   The sum matrix, one row per line.

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

int main(){int n,m; cin>>n>>m; vector<vector<int>> a(n,vector<int>(m)),b=a; for(auto &r:a) for(int &x:r) cin>>x; for(auto &r:b) for(int &x:r) cin>>x; for(int i=0;i<n;i++){for(int j=0;j<m;j++) cout<<a[i][j]+b[i][j]<<(j+1==m?'\n':' ');}}
