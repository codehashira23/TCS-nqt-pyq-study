/*
   TCS NQT PYQ 01: Odd Occurring Element in O(log N)
   Source: Verified PYQ
   Difficulty: Hard
   Topics: Array, Binary Search

   QUESTION
   Given an array of integers where every element appears an even number of times except one element which appears an odd number of times, find that odd-occurring element in O(log N) time. Equal elements appear in pairs and no element appears more than two times consecutively.

   CONSTRAINTS
   - 1 <= N <= 1000 for DP/backtracking style inputs; use modulo where asked.
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
    int n; cin>>n; vector<long long>a(n); for(auto &x:a) cin>>x;
    int l=0,r=n-1;
    while(l<r){int m=l+(r-l)/2; if(m%2) m--;
        if(m+1<n && a[m]==a[m+1]) l=m+2; else r=m;
    }
    cout<<a[l]<<"\n";
}
