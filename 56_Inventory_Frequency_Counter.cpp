/*
   TCS NQT PYQ 56: Inventory Frequency Counter
   Source: Verified PYQ
   Difficulty: Easy
   Topics: String, Hash Map

   QUESTION
   Given a string of space-separated item names (inventory), count how many times each item appears. If the input contains any digit, print "Invalid input" and stop.

   CONSTRAINTS
   - 1 <= length of string <= 100000.
   - Input is assumed valid unless the problem explicitly asks for validation.
   - Use O(N) or better whenever a direct traversal solution exists.

   INPUT FORMAT
   The string input described in the question.

   OUTPUT FORMAT
   The required string/count/result.

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

int main(){string line,item; getline(cin,line); for(char c:line) if(isdigit((unsigned char)c)){cout<<"Invalid input\n"; return 0;} stringstream ss(line); map<string,int> f; while(ss>>item) f[item]++; for(auto &p:f) cout<<p.first<<" "<<p.second<<"\n";}
