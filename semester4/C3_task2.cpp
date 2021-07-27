#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using Vertex = size_t;
using std::vector;
using std::pair;

template<class T>
class DisjSet
{
    std::unordered_map<T, T> parent; //{kid, its parent}
    std::unordered_map<T, size_t> rank;

    const T& getRoot(const T& x)
    {
        if (parent[x] == x)
            return x;
        const T& res = getRoot(parent[x]);
        parent[x] = res;
        return res;
    }

public:
    DisjSet() = default;

    void add(const T& x)
    {
        if (rank.count(x))
            return;
        rank[x] = 0;
        parent[x] = x;
    }

    void unite(const T& x, const T& y)
    {
        auto xRoot = getRoot(x);
        auto yRoot = getRoot(y);

        if (xRoot == yRoot)
            return;   
        if (rank[xRoot] > rank[yRoot])
            parent[yRoot] = xRoot;
        else if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;
        else
        {
            //ranks are equal
            parent[yRoot] = xRoot;
            ++rank[xRoot];
        }
    }

    bool inSameSet(const T& x, const T& y)
    {
        return getRoot(x) == getRoot(y);
    }
};

struct Edge
{
    Vertex vFrom;
    Vertex vTo;
    size_t weight;
};

size_t minSpanTreeWeight(vector<Edge>& edges)
{
    std::sort(edges.begin(), edges.end(),
              [](Edge& e1, Edge& e2) {return e1.weight < e2.weight;});

    DisjSet<Vertex> dset;
    size_t res = 0;
    for (auto& e : edges)
    {
        dset.add(e.vFrom);
        dset.add(e.vTo);

        if(dset.inSameSet(e.vFrom, e.vTo))
            continue;
        
        res += e.weight;
        dset.unite(e.vFrom, e.vTo);
    }
    return res;
}

int main()
{
    size_t vCount, eCount;
    std::cin >> vCount >> eCount;

    std::vector<Edge> edges;
    for (auto i = 0; i < eCount; ++i)
    {
        Vertex from, to;
        size_t w;
        std::cin >> from >> to >> w;
        edges.push_back({from - 1, to - 1, w});
    }
    std::cout << minSpanTreeWeight(edges);
}