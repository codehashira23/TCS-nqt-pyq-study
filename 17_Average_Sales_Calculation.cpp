/*
   TCS NQT PYQ 17: Average Sales Calculation
   Source: Verified PYQ
   Exam/Shift: 26 April 2024 Shift 1
   Difficulty: Easy
   Topics: Math, Simulation

   QUESTION
   A shopkeeper has N items for sale. Each item has a name, price per unit, and quantity. Calculate the average sales value across all items where sales for an item is price * quantity.

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

int main(){int n; cin>>n; double total=0; for(int i=0;i<n;i++){string name; double price,qty; cin>>name>>price>>qty; total+=price*qty;} cout<<fixed<<setprecision(2)<<total/n<<"\n";}
