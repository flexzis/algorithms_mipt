#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using Vertex = size_t;

class IGraph {
public:
    virtual ~IGraph() {}

    virtual void AddEdge(Vertex from, Vertex to) = 0;

    virtual size_t VCount() const = 0;

    virtual vector<Vertex> GetAdj(Vertex v) const = 0;
};

class NonOrGraph : public IGraph
{
private:
    vector<vector<Vertex>> graph;

public:
    NonOrGraph() = default;

    explicit NonOrGraph(size_t vCount) : graph(vCount) {}

    NonOrGraph(const NonOrGraph& gr) : graph{ gr.graph } {}

    NonOrGraph(NonOrGraph&& gr) noexcept : graph{ std::move(gr.graph) } {}

    void AddEdge(Vertex from, Vertex to) override
    {
        graph.at(from).push_back(to);
        graph.at(to).push_back(from);
    }

    size_t VCount() const override
    {
        return graph.size();
    }

    vector<Vertex> GetAdj(Vertex v) const override
    {
        return graph.at(v);
    }
};

enum class Color
{
    Black, White, Gray
};

vector<Vertex> BFS(const IGraph& graph, Vertex v)
{
    vector<size_t> distances(graph.VCount());
    if(!graph.VCount())
        return distances;
    distances.at(v) = 0;

    vector<Color> colors(graph.VCount(), Color::White);
    std::queue<std::pair<Vertex, size_t>> q;
    q.push({v, 0});

    while(!q.empty())
    {
        auto cur = q.front();
        q.pop();
        auto curAdj = graph.GetAdj(cur.first);
        for (auto nextV : curAdj)
        {
            if(colors[nextV] == Color::White)
            {
                auto distFromV = cur.second + 1;
                distances[nextV] = distFromV; 
                q.push({nextV, distFromV});
                colors[nextV] = Color::Gray;
            }
        }
        colors[cur.first] = Color::Black;
    }

    return distances;
}

size_t MinDist(const vector<size_t>& d1, const vector<size_t>& d2, const vector<size_t>& d3)
{
    size_t minDist = -1;
    for (auto i = 0; i < d1.size(); ++i)
    {
        auto curDist = d1[i] + d2[i] + d3[i];
        if (curDist < minDist)
            minDist = curDist;
    }
    return minDist;
}

int main()
{
    size_t vCount, eCount;
    std::cin >> vCount >> eCount;

    Vertex v1, v2, v3;
    std::cin >> v1 >> v2 >> v3;

    NonOrGraph g(vCount);
    for(auto i = 0; i < eCount; ++i)
    {
        Vertex from, to;
        std::cin >> from >> to;
        g.AddEdge(from - 1, to - 1);
    }

    vector<size_t> d1, d2, d3;
    d1 = BFS(g, v1 - 1);
    d2 = BFS(g, v2 - 1);
    d3 = BFS(g, v3 - 1);

    std::cout << MinDist(d1, d2, d3);
}