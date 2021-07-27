#include <cstring>
#include <iostream>
#include <math.h>
#include <set>
#include <vector>

using namespace std;

int best_cost = 1000000000;

vector<int> mincut(vector<vector<int>>& g)
{
    int N = g.size();
    vector<int> best_cut;

    vector<int> v[N];
    for (int i = 0; i < N; ++i)
        v[i].assign(1, i);
    int w[N];
    bool exist[N], in_a[N];
    memset(exist, true, sizeof exist);
    for (int ph = 0; ph < N - 1; ++ph)
    {
        memset(in_a, false, sizeof in_a);
        memset(w, 0, sizeof w);
        for (int it = 0, prev; it < N - ph; ++it)
        {
            int sel = -1;
            for (int i = 0; i < N; ++i)
                if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel]))
                    sel = i;
            if (it == N - ph - 1)
            {
                if (w[sel] < best_cost)
                    best_cost = w[sel], best_cut = v[sel];
                v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
                for (int i = 0; i < N; ++i)
                    g[prev][i] = g[i][prev] += g[sel][i];
                exist[sel] = false;
            }
            else
            {
                in_a[sel] = true;
                for (int i = 0; i < N; ++i)
                    w[i] += g[sel][i];
                prev = sel;
            }
        }
    }

    return best_cut;
}

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> widths(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i)
    {
        string str;
        cin >> str;

        for (int j = 0; j < N; ++j)
        {
            if (str[j] == '0')
                continue;

            widths[i][j] = 1;
        }
    }

    vector<int> cut = mincut(widths);
    vector<int> vertexes(N, 0);
    for (auto el : cut)
    {
        vertexes[el] = 1;
        cout << el + 1 << " ";
    }

    cout << endl;

    for (int i = 0; i < N; ++i)
        if (vertexes[i] == 0)
            cout << i + 1 << " ";

    return 0;
}