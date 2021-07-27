#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <string>

using std::cin, std::cout;
using std::vector, std::pair, std::queue;
using OrGraph = vector<vector<bool>>;

size_t DFS(const OrGraph& g, size_t s, size_t t, vector<size_t>& path)
{
   std::stack<size_t> st;
   vector<size_t> parent(g.size());
   vector<char> visited(g.size(), 0);

   st.push(s);
   parent[s] = -1;
   visited[s] = true;
   while (!st.empty())
   {
       auto curV = st.top();
       st.pop();
       for (auto i = 0; i < g.size(); ++i)
       {
           if (!visited[i] && g[curV][i])
           {
               st.push(i);
               parent[i] = curV;
               visited[i] = true;
           }
       }
   }
   if (!visited[t]) return 0;
   for (auto curV = t; ; curV = parent[curV])
   {
       path.push_back(curV);
       if (curV == s) break;
   }
   std::reverse(path.begin(), path.end());
   return path.size() - 1;
}

size_t GetMinCut(size_t s, size_t t, const OrGraph& g, OrGraph& gResidual)
{
   //min cut = max flow
   size_t maxFlow = 0;
   for(;;)
   {
       vector<size_t> path;
       auto curFlow = DFS(gResidual, s, t, path);
       if (curFlow == 0)
           break;
       maxFlow += curFlow;
       for (auto i = 0; i < path.size() - 1; ++i)
           gResidual[path[i]][path[i + 1]] = false;
   }
   return maxFlow;
}

vector<bool> MinCutSeparation(const OrGraph& g)
{
   auto s = 0;
   auto minCutVertex = 1;
   auto minGResidual = g;
   auto minCut = GetMinCut(s, minCutVertex, g, minGResidual);
   for (auto curV = 2; curV < g.size(); ++curV)
   {
       auto curGResidual = g;
       auto curCut = GetMinCut(s, curV, g, curGResidual);
       if (curCut < minCut)
       {
           minGResidual = curGResidual;
           minCutVertex = curV;
           minCut = curCut;
       }
   }
   //dfs on minGResidiual
   vector<bool> visited(g.size(), false);
   visited[s] = true;
   std::stack<size_t> st;
   st.push(s);
   while(!st.empty())
   {
       auto curV = st.top();
       st.pop();
       for (auto nextV = 0; nextV < minGResidual.size(); ++nextV)
       {
           if (!visited[nextV] && minGResidual[curV][nextV])
           {
               st.push(nextV);
               visited[nextV] = true;
           }
       }
   }  
   return visited;  
}

int main()
{
   size_t n;
   cin >> n;
   OrGraph gr(n, vector<bool>(n, 0));
   for (auto i = 0; i < n; ++i)
   {
       std::string s;
       cin >> s;
       for (auto j = 0; j < n; ++j)
           gr[i][j] = s[j] - '0';
   }
   vector<bool> res = MinCutSeparation(gr);
   for (auto i = 0; i < n; ++i)
       if(res[i])
           cout << i + 1 << " ";
   cout << "\n";
   for (auto i = 0; i < n; ++i)
       if(!res[i])
           cout << i + 1 << " ";
}
