#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
struct Node
{
	int parent = -1;
	std::vector<int> childs;
	int dist_down = 0;
	int dist_up = 0;
	int maxDist()
	{
		return std::max(dist_down, dist_up);
	}
};

int countDistDown(int h, std::vector<Node<int>>& tree)
{
	//set all DownDistances automatically if started froom root
	if (tree[h].childs.empty())
		return 0;
    if (h == 0)
        return 0;
	for (auto& child : tree[h].childs)
	{
		int curDepth = countDistDown(child, tree);
		if (curDepth >= tree[h].dist_down)
			tree[h].dist_down = 1 + curDepth;
	}
	return tree[h].dist_down;
}

int countDistUp(int h, std::vector<Node<int>>& tree)
{
	//must be started from root and downDistances need to be set

	if (tree[h].dist_up != 0)
		return tree[h].maxDist();

	if (h == 0)
		return tree[h].dist_down;

	int p = tree[h].parent;
	if (tree[p].maxDist() != tree[h].dist_down + 1)
	{
		tree[h].dist_up = tree[p].maxDist() + 1;
	}
	else
	{
		for (auto& child : tree[p].childs)
			if (child != h and tree[h].dist_up < tree[child].dist_down + 2)
				tree[h].dist_up = tree[child].dist_down + 2;

		if (tree[h].dist_up < tree[p].dist_up + 1)
			tree[h].dist_up = tree[p].dist_up + 1;
	}
	return tree[h].maxDist();
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<Node<int>> tree(n);
	for (int i = 0; i < n - 1; ++i)
	{
		int par, child;
		std::cin >> par >> child;
		tree[par].childs.push_back(child);
		tree[child].parent = par;
	}
	countDistDown(0, tree);
	
	for (int i = 0; i < n; ++i)
		std::cout << countDistUp(i, tree) << " ";
}