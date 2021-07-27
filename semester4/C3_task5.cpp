#include <iostream>
#include <vector>
#include <algorithm>

using std::cin, std::cout;
using std::vector, std::pair, std::queue;
using OrGraph = vector<vector<int>>;

void _DFS(int curV, const OrGraph& g, vector<int>& parent, vector<bool>& visited, int t)
{
   visited[curV] = true;
   if (curV == t)
       return;
   for (auto i = 0; i < g.size(); ++i)
   {
       if (!visited[i] && g[curV][i] > 0)
       {
           parent[i] = curV;
           _DFS(i, g, parent, visited, t);
       }
   }
}

bool DFS(const OrGraph& g, int s, int t, vector<int>& path)
{
   vector<int> parent(g.size());
   vector<bool> visited(g.size(), false);

   parent[s] = -1;
   visited[s] = true;
   _DFS(s, g, parent, visited, t);
   if (!visited[t]) return false;
   for (auto curV = t; ; curV = parent[curV])
   {
       path.push_back(curV);
       if (curV == s) break;
   }
   std::reverse(path.begin(), path.end());
   return true;
}

pair<vector<int>, vector<int>> FindPaths(OrGraph& g, int s, int t)
{
   vector<int> path1, path2;
   OrGraph gR = g;
   if (!DFS(gR, s, t, path1))
       return { vector<int>(), vector<int>() };

   for (auto i = 0; i < path1.size() - 1; ++i)
       --gR[path1[i]][path1[i + 1]];

   if (!DFS(gR, s, t, path2))
       return { path1, vector<int>() };

   return { path1, path2 };
}

int main()
{
   int n, m, s, t;
   cin >> n >> m >> s >> t;
   --s; --t;
   OrGraph gr(n, vector<int>(n, 0));
   for (auto i = 0; i < m; ++i)
   {
       int from, to;
       cin >> from >> to;
       if (from == to) continue;
       ++gr[from - 1][to - 1];
   }

   auto [path1, path2] = FindPaths(gr, s, t);
   if (path1.empty() || path2.empty())
       cout << "NO";
   else
   {
       cout << "YES" << "\n";
       for (auto x : path1) cout << x + 1 << " ";
       cout << "\n";
       for (auto x : path2) cout << x + 1 << " ";
   }
   cout << "\n";
}
