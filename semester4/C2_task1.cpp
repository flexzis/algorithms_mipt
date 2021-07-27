#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <queue>
#include <random>

using std::vector;
using Vertex = size_t;
using std::pair;

class IWGraph
{
public:
    virtual ~IWGraph() {}

    virtual void AddEdge(Vertex from, Vertex to, size_t weight) = 0;

    virtual size_t VCount() const = 0;

    virtual vector<pair<Vertex, size_t>> GetAdj(Vertex v) const = 0;
};

class WOrGraph : public IWGraph
{
private:
    vector<vector<pair<Vertex, size_t>>> graph;
public:
    WOrGraph() = default;
    explicit WOrGraph(size_t vCount) : graph(vCount) {}
    WOrGraph(vector<vector<pair<Vertex, size_t>>> graph) : graph{ graph } {}
    WOrGraph(const WOrGraph& gr) : graph{ gr.graph } {}
    WOrGraph(WOrGraph&& gr) noexcept : graph{ std::move(gr.graph) } {}

    void AddEdge(Vertex from, Vertex to, size_t weight) override
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

    vector<pair<Vertex, size_t>> GetAdj(Vertex v) const override
    {
        return graph.at(v);
    }
};


enum class Color
{
    White, Black, Grey
};

vector<size_t> Dijkstra(const WOrGraph& gr, Vertex v)
{
    const size_t inf = -1;
    vector<size_t> dist(gr.VCount(), inf);
    dist[v] = 0;
    vector<Color> colors(gr.VCount(), Color::White);
    using T = pair<size_t, Vertex>;
    std::priority_queue<T, vector<T>, std::greater<T>> q;
    q.push({ 0, v });

    while (!q.empty())
    {
        auto [curD, curV] = q.top();
        q.pop();

        colors[curV] = Color::Black;

        for (auto [nextV, nextD] : gr.GetAdj(curV))
        {
            if (dist[nextV] > curD + nextD)
            {
                dist[nextV] = curD + nextD;
                if (colors[nextV] == Color::White)
                    q.push({ dist[nextV], nextV });
            }
        }
    }
    return dist;
}
//int main()
//{
//    size_t a, b, M, vFrom, vTo;
//    std::cin >> a >> b >> M >> vFrom >> vTo;
//    WOrGraph g(M);
//    for (auto v = 0; v < M; ++v)
//    {
//        g.AddEdge(v, (v * v + 1) % M, b);
//        g.AddEdge(v, (v + 1) % M, a);
//    }
//    std::cout << Dijkstra(g, vFrom)[vTo];
//}