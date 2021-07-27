#include <iostream>
#include <vector>

using Vertex = size_t;
using std::vector;
using std::pair;
using std::cin, std::cout;

struct RC
{
    double rate;
    double comission;
    double GetValue(double value)
    {
        return (value - comission) * rate;
    }
};

class WOrGraph
{
private:
    vector<vector<pair<Vertex, RC>>> graph;

public:
    WOrGraph() = default;
    explicit WOrGraph(size_t vCount) : graph(vCount) {}

    void AddEdge(Vertex from, Vertex to, RC weight)
    {
        graph.at(from).push_back({ to, weight });
    }

    size_t VCount() const
    {
        return graph.size();
    }

    vector<pair<Vertex, RC>> GetAdj(Vertex v) const
    {
        vector<pair<Vertex, RC>> adj(graph.at(v).size());
        for (auto i = 0; i < adj.size(); ++i)
            adj[i] = graph.at(v)[i];
        return adj;
    }
};

bool HasCycle(const WOrGraph& gr, int startCur, double value)
{
    vector<double> values(gr.VCount(), 0);
    values[startCur] = value;

    for (auto i = 0; i < gr.VCount() - 1; ++i)
        for (auto v = 0; v < gr.VCount(); ++v)
            for (auto[u, uRC] : gr.GetAdj(v))
            {
                auto Wvu = uRC.GetValue(values[v]);
                if (values[u] < Wvu)
                    values[u] = Wvu;
            }
    for (auto v = 0; v < gr.VCount(); ++v)
        for (auto[u, uRC] : gr.GetAdj(v))
        {
            auto Wvu = uRC.GetValue(values[v]);
             if (values[u] < Wvu)
                return true;
        }
    return false;
}

int main()
{
    int N, M, S;
    double V;
    cin >> N >> M >> S >> V;
    WOrGraph gr(N);
    for (auto i = 0; i < M; ++i)
    {   
        Vertex vFrom, vTo;
        RC rc;
        cin >> vFrom >> vTo;
        cin >> rc.rate >> rc.comission;
        gr.AddEdge(vFrom - 1, vTo - 1, rc);
        cin >> rc.rate >> rc.comission;
        gr.AddEdge(vTo - 1, vFrom - 1, rc);
    }

    cout << (HasCycle(gr, S - 1, V) ? "YES" : "NO");
}