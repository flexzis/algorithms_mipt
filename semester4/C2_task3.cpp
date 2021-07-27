#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <queue>
#include <random>
#include <iomanip>

using std::vector;
using Vertex = size_t;
using std::pair;

class IWGraph {
public:
    virtual ~IWGraph() {}

    virtual void AddEdge(Vertex from, Vertex to, double weight) = 0;

    virtual size_t VCount() const = 0;

    virtual vector<pair<Vertex, double>> GetAdj(Vertex v) const = 0;
};

class WGraph : public IWGraph
{
private:
    vector<vector<pair<Vertex, double>>> graph;
public:
    WGraph() = default;
    explicit WGraph(size_t vCount) : graph(vCount) {}
    WGraph(vector<vector<pair<Vertex, double>>> graph) : graph{ graph } {}
    WGraph(const WGraph& gr) : graph{ gr.graph } {}
    WGraph(WGraph&& gr) noexcept : graph{ std::move(gr.graph) } {}

    void AddEdge(Vertex from, Vertex to, double weight) override
    {
        graph.at(from).push_back({ to, weight });
        graph.at(to).push_back({ from, weight });
    }

    size_t VCount() const override
    {
        return graph.size();
    }

    vector<pair<Vertex, double>> GetAdj(Vertex v) const override
    {
        return graph.at(v);
    }
};

enum class Color
{
    White, Black, Grey
};

vector<double> Dijkstra(const WGraph& gr, Vertex v)
{
    vector<double> prob(gr.VCount(), -1); //probabilities of Rick not to be punched
    prob[v] = 1;

    std::priority_queue<pair<double, Vertex>> q;
    q.push({ 1, v });

    vector<Color> colors(gr.VCount(), Color::White);

    while (!q.empty())
    {
        auto [curP, curV] = q.top();
        colors[curV] = Color::Black;
        q.pop();

        for (auto& [nextV, nextP] : gr.GetAdj(curV))
        {
            if (prob[nextV] < curP * nextP)
            {
                prob[nextV] = curP * nextP;
                if (colors[nextV] == Color::White)
                    q.push({ prob[nextV], nextV });
            }
        }
    }
    return prob;
}

//int main()
//{
//    size_t vCount, eCount;
//    Vertex vFrom, vTo;
//    std::cin >> vCount >> eCount >> vFrom >> vTo;
//
//    WGraph g(vCount);
//    for (auto i = 0; i < eCount; ++i)
//    {
//        Vertex v1, v2;
//        double w;
//        std::cin >> v1 >> v2 >> w;
//        g.AddEdge(v1 - 1, v2 - 1, 1 - w / 100.);
//    }
//
//    std::cout << std::setprecision(6) << (1 - Dijkstra(g, vFrom - 1)[vTo - 1]);
//}
