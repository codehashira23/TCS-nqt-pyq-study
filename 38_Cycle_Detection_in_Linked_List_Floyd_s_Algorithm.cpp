/*
   TCS NQT PYQ 38: Cycle Detection in Linked List (Floyd's Algorithm)
   Source: Practice
   Difficulty: Medium
   Topics: Linked List

   QUESTION
   Given a singly linked list, detect whether it contains a cycle. Print "Cycle Detected" if there is a cycle, otherwise print "No Cycle".

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

struct Node{int data; Node*next; Node(int x):data(x),next(nullptr){}}; int main(){int n,pos; cin>>n>>pos; vector<Node*> nodes; for(int i=0,x;i<n;i++){cin>>x; nodes.push_back(new Node(x)); if(i) nodes[i-1]->next=nodes[i];} if(pos>=0&&pos<n) nodes.back()->next=nodes[pos]; Node *slow=nodes[0],*fast=nodes[0]; bool cycle=false; while(fast&&fast->next){slow=slow->next; fast=fast->next->next; if(slow==fast){cycle=true; break;}} cout<<(cycle?"Cycle Detected":"No Cycle")<<"\n";}
