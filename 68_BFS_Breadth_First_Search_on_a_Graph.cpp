/*
   TCS NQT PYQ 68: BFS (Breadth First Search) on a Graph
   Source: Verified PYQ
   Difficulty: Medium
   Topics: Graph, BFS

   QUESTION
   Given an undirected graph with V vertices and E edges, perform BFS starting from vertex 0 and print the traversal order.

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

int main(){int V,E; cin>>V>>E; vector<vector<int>> g(V); for(int i=0,u,v;i<E;i++){cin>>u>>v; g[u].push_back(v); g[v].push_back(u);} for(auto &v:g) sort(v.begin(),v.end()); vector<int> vis(V); queue<int> q; q.push(0); vis[0]=1; while(!q.empty()){int u=q.front(); q.pop(); cout<<u<<" "; for(int v:g[u]) if(!vis[v]) vis[v]=1,q.push(v);} cout<<"\n";}
