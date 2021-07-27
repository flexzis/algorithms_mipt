//#include <vector>
//#include <iostream>
//#include <queue>
//#include <unordered_map>
//#include <unordered_set>
//#include <algorithm>
//
//using Vertex = size_t;
//using std::vector;
//using std::pair;
//
//class WGraph
//{
//private:
//    vector<vector<pair<Vertex, size_t>>> graph;
//public:
//    WGraph() = default;
//    explicit WGraph(size_t vCount) : graph(vCount) {}
//
//    void AddEdge(Vertex from, Vertex to, size_t weight)
//    {
//        graph.at(to).push_back({ from, weight });
//        graph.at(from).push_back({ to, weight });
//    }
//
//    size_t VCount() const
//    {
//        return graph.size();
//    }
//
//    vector<pair<Vertex, size_t>> GetAdj(Vertex v) const
//    {
//        return graph.at(v);
//    }
//};
//
//struct Edge
//{
//    Vertex vFrom;
//    Vertex vTo;
//    size_t weight;
//
//    bool operator > (const Edge& other) const noexcept
//    {
//        return weight > other.weight;
//    }
//};
//
//size_t minSpanTreeWeight(const WGraph& gr)
//{
//    size_t res = 0;
//    std::priority_queue<Edge, vector<Edge>, std::greater<Edge>> q;
//    std::unordered_set<Vertex> visited;
//    visited.insert(0);
//
//    for (auto [vTo, weight] : gr.GetAdj(0))
//    {
//        Edge curE = { 0, vTo, weight };
//        if (!visited.count(vTo))
//            q.push(curE);
//    }
//
//    while (visited.size() < gr.VCount())
//    {
//        while (visited.count(q.top().vTo)) q.pop();
//        Edge curEdge = q.top();
//        q.pop();
//        res += curEdge.weight;
//        visited.insert(curEdge.vTo);
//
//
//        for (auto [vTo, weight] : gr.GetAdj(curEdge.vTo))
//        {
//            Edge curE = { curEdge.vTo, vTo, weight };
//            if (!visited.count(vTo))
//                q.push(curE);
//        }
//    }
//    return res;
//}
//
//int main()
//{   
//    size_t vCount, m;
//    std::cin >> vCount >> m;
//    WGraph graph(vCount);
//    std::vector<size_t> vcost(vCount);
//    for (auto& x : vcost)
//        std::cin >> x;
//    Vertex minV = std::min_element(vcost.begin(), vcost.end()) - vcost.begin();
//    for(auto i = 0; i < vCount; ++i)
//    {
//        if (i == minV)
//            continue;
//        graph.AddEdge(minV, i, vcost[minV] + vcost[i]);
//    }
//    for (auto i = 0; i < m; ++i)
//    {
//        Vertex from, to;
//        size_t weight;
//        std::cin >> from >> to >> weight;
//        graph.AddEdge(from - 1, to - 1, weight);
//    }
//    std::cout << minSpanTreeWeight(graph);
//}