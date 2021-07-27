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

void DFS_TopSort(const IGraph& graph, Vertex v, vector<Color>& colors, vector<Vertex>& ans)
{
	if (!graph.VCount())
		return;

	std::stack<std::pair<Vertex, Vertex>> st;

	st.push({ v, 0 });
	colors[v] = Color::Gray;

	while (!st.empty())
	{
		auto cur = st.top();
		auto curAdj = graph.GetAdj(cur.first);
		for (auto nextV : curAdj)
		{
			if (colors[nextV] == Color::White)
			{
				st.push({ nextV, cur.first });
				colors[nextV] = Color::Gray;
				break;
			}

			if (colors[nextV] == Color::Gray)
			{
				ans.clear();
				return;
			}
		}

		if (st.top() == cur)
		{
			ans.push_back(cur.first);
			colors[st.top().first] = Color::Black;
			st.pop();

			auto prevAdj = graph.GetAdj(cur.second);
			for (auto nextV : prevAdj)
			{
				if (colors[nextV] == Color::White)
				{
					st.push({ nextV, cur.second });
					colors[nextV] = Color::Gray;
					break;
				}

				if (colors[nextV] == Color::Gray)
				{
					ans.clear();
					return;
				}
			}
		}
	}
}

std::vector<Vertex> TopSort(const IGraph& graph)
{
	vector<Vertex> ans;
	vector<Color> colors(graph.VCount(), Color::White);

	for (auto v = 0; v < graph.VCount(); ++v)
	{
		if (colors[v] == Color::White)
			DFS_TopSort(graph, v, colors, ans);
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