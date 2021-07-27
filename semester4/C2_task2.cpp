#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <queue>
#include <random>
#include <cmath>

using std::vector;
using Vertex = size_t;
using std::pair;
const int inf = pow(10, 7);

class IWGraph
{
public:
    virtual ~IWGraph() {}

    virtual void AddEdge(Vertex from, Vertex to, int weight) = 0;

    virtual size_t VCount() const = 0;

    virtual vector<Vertex> GetAdj(Vertex v) const = 0;
};

class WOrGraph : public IWGraph
{
private:
    vector<vector<pair<Vertex, int>>> graph;

public:
    WOrGraph() = default;
    explicit WOrGraph(int vCount) : graph(vCount) {}
    WOrGraph(vector<vector<pair<Vertex, int>>> graph) : graph{ graph } {}
    WOrGraph(const WOrGraph& gr) : graph{ gr.graph } {}
    WOrGraph(WOrGraph&& gr) noexcept : graph{ std::move(gr.graph) } {}

    void AddEdge(Vertex from, Vertex to, int weight) override
    {
        for (auto& x : graph.at(from))
        {
            if (x.first == to)
            {
                x.second = std::min(x.second, weight);
                return;
            }
        }
        graph.at(from).push_back({ to, weight });
    }

    size_t VCount() const override
    {
        return graph.size();
    }

    vector<Vertex> GetAdj(Vertex v) const override
    {
        vector<Vertex> adj(graph.at(v).size());
        for (auto i = 0; i < adj.size(); ++i)
            adj[i] = graph.at(v)[i].first;
        return adj;
    }

    int GetWeight(Vertex from, Vertex to) const
    {
        for (auto& x : graph.at(from))
            if (x.first == to)
                return x.second;
        return inf;
    }
};

enum class Color
{
    White, Black, Grey
};

int FordBellman(const WOrGraph& gr, Vertex vFrom, Vertex vTo, int maxLen)
{
    vector<int> dist(gr.VCount(), inf);
    dist[vFrom] = 0;

    for (auto i = 0; i < maxLen; ++i)
    {
        bool changed = 0;
        vector<int> was_changed(dist.size(), 0);
        for (auto v = 0; v < gr.VCount(); ++v)
        {
            for (auto u = 0; u < gr.VCount(); ++u)
            {
                auto Wuv = gr.GetWeight(u, v);
                if (Wuv != inf and !was_changed[u] and dist[v] > dist[u] + Wuv)
                {
                    dist[v] = dist[u] + Wuv;
                    was_changed[v] = 1;
                    changed = 1;
                }
            }
        }
        if (!changed)
            break;
    }
    if (dist[vTo] == inf)
        return -1;
    return dist[vTo];
}

//int main()
//{
//    int vCount, eCount, maxLen, vFrom, vTo;
//    std::cin >> vCount >> eCount >> maxLen >> vFrom >> vTo;
//
//    WOrGraph g(vCount);
//    for (auto i = 0; i < eCount; ++i)
//    {
//        Vertex v1, v2, w;
//        std::cin >> v1 >> v2 >> w;
//        g.AddEdge(v1 - 1, v2 - 1, w);
//    }
//
//    std::cout << FordBellman(g, vFrom - 1, vTo - 1, maxLen);
//}