#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using std::vector;
using Vertex = size_t;

class IGraph {
public:
	virtual ~IGraph() {}

	virtual void AddEdge(Vertex from, Vertex to) = 0;

	virtual size_t VCount() const = 0;

	virtual vector<Vertex> GetAdj(Vertex v) const = 0;
};

class OrGraph : public IGraph
{
private:
	vector<vector<Vertex>> graph;

public:
	OrGraph() = default;
	explicit OrGraph(size_t vCount) : graph(vCount) {}
	OrGraph(const OrGraph& gr) : graph{ gr.graph } {}
	OrGraph(OrGraph&& gr) noexcept : graph{ std::move(gr.graph) } {}

	void AddEdge(Vertex from, Vertex to) override
	{
		graph.at(from).push_back(to);
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

int DFS_TopSort(const IGraph& g, Vertex v, vector<Color>& colors, vector<Vertex>& ans)
{
    colors[v] = Color::Gray;
    for (auto x : g.GetAdj(v))
    {
        if (colors[x] == Color::Gray)
        {
            ans.clear();
            return -1; //cycle found
        }

        if (colors[x] == Color::White)
            if (DFS_TopSort(g, x, colors, ans) == -1)
                return;
    }
    colors[v] = Color::Black;
    ans.push_back(v);
    return 0;
}

std::vector<Vertex> TopSort(const IGraph& graph)
{
	vector<Vertex> ans;
	vector<Color> colors(graph.VCount(), Color::White);

	for (auto v = 0; v < graph.VCount(); ++v)
	{
		if (colors[v] == Color::White)
			if (DFS_TopSort(graph, v, colors, ans) < 0)
                return ans;
	}
	if (!ans.empty())
		std::reverse(ans.begin(), ans.end());

	return ans;
}

int main()
{
	size_t vCount, eCount;
	std::cin >> vCount >> eCount;

	OrGraph g(vCount);
	for (int i = 0; i < eCount; ++i)
	{
		Vertex from, to;
		std::cin >> from >> to;
		g.AddEdge(from, to);
	}

	auto ans = TopSort(g);
	if (ans.empty())
	{
		std::cout << "NO";
	}
	else
	{
		std::cout << "YES" << std::endl;
		for (auto v : ans)
			std::cout << v << " ";
	}
	std::cout << std::endl;
}