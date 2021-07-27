#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using std::vector;
using Vertex = size_t;

class OrGraph 
{
private:
	vector<vector<Vertex>> graph;
public:
	OrGraph() = default;
	explicit OrGraph(size_t vCount) : graph(vCount) {}

	void AddEdge(Vertex from, Vertex to)
	{
		graph.at(from).push_back(to);
	}

	size_t VCount() const 
	{
		return graph.size();
	}

	vector<Vertex> GetAdj(Vertex v) const
	{
		return graph.at(v);
	}
};

enum class Color
{
	Black, White, Gray
};

OrGraph GetReversed(const OrGraph& gr)
{
    OrGraph grR(gr.VCount());
    for (auto i = 0; i < gr.VCount(); ++i)
        for (auto j : gr.GetAdj(i))
            grR.AddEdge(j, i);
    return grR;
}

void DFS_GetOrder(Vertex v, const OrGraph& gr, vector<Color>& colors,
                  vector<Vertex>& order)
{
    colors[v] = Color::Gray;
    for (auto nextV : gr.GetAdj(v))
        if(colors[nextV] == Color::White)
            DFS_GetOrder(nextV, gr, colors, order);

    colors[v] == Color::Black;
    order.push_back(v);
}

void DFS_Numerate(Vertex v, const OrGraph& gr, vector<Color>& colors,
                  vector<size_t>& component, size_t curComp)
{
    colors[v] = Color::Gray;
    for (auto nextV : gr.GetAdj(v))
        if(colors[nextV] == Color::White)
           DFS_Numerate(nextV, gr, colors, component, curComp);

    colors[v] == Color::Black;
    component[v] = curComp;
 }

std::pair<vector<size_t>, size_t> GetComponents(const OrGraph& gr)
{
    size_t ans = 0;
    OrGraph grR = GetReversed(gr);
    vector<Vertex> order;
    vector<Color> colors(gr.VCount(), Color::White);

    for (Vertex i = 0; i < gr.VCount(); ++i)
        if (colors[i] == Color::White)
            DFS_GetOrder(i, grR, colors, order);

    std::reverse(order.begin(), order.end());
    std::fill(colors.begin(), colors.end(), Color::White);

    vector<size_t> component(gr.VCount());
    size_t curComp = 0;

    for(auto v : order)
        if (colors[v] == Color::White)
                DFS_Numerate(v, gr, colors, component, curComp++);

    return {component, curComp};
}

size_t EdgesNeeded(const vector<size_t>& component, int compAmount, const OrGraph& gr)
{
    if (compAmount <= 1)
        return 0;

    vector<char> isSource(compAmount, false);
    vector<char> isStock(compAmount, false);
    for (Vertex v = 0; v < gr.VCount(); ++v)
    {
        for (auto nextV : gr.GetAdj(v))
        if(component[v] != component[nextV])
        {
            isSource[component[v]] = true;
            isStock[component[nextV]] = true;
        }
    }
    return std::max(std::count(isSource.begin(), isSource.end(), false),
                    std::count(isStock.begin(), isStock.end(), false));
}

int main ()
{
    size_t vCount, eCount;
    std::cin >> vCount >> eCount;

    OrGraph g(vCount);
    for(auto i = 0; i < eCount; ++i)
    {
        Vertex from, to;
        std::cin >> from >> to;
        g.AddEdge(from - 1, to - 1);
    }
    auto[component, compAmount] = GetComponents(g);
    std::cout << EdgesNeeded(component, compAmount, g);
}