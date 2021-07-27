#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
	int parent = -1;
	std::vector<int> childs;
	int down_nodes = 0;
	int up_nodes = 0;
	int down_dist = 0;
	int upDist = 0;
};
 
int countNodesDown(int h, std::vector<Node>& tree)
{
	for (auto child : tree[h].childs)
		tree[h].down_nodes += countNodesDown(child, tree);

	return tree[h].down_nodes + 1;
}

void countNodesUp(int h, std::vector<Node>& tree)
{
	int p = tree[h].parent;
	tree[h].up_nodes = tree[p].down_nodes - tree[h].down_nodes + tree[p].up_nodes;
}

int findDownDist(int h, std::vector<Node>& tree)
{
	for (auto child : tree[h].childs)
	{
		++tree[h].down_dist;
		tree[h].down_dist += findDownDist(child, tree) + tree[child].down_nodes;
	}
	return tree[h].down_dist;
}

void findUpDist(int h, std::vector<Node>& tree)
{
	int p = tree[h].parent;
	tree[h].upDist = tree[p].down_dist + tree[p].down_nodes
		- (tree[h].down_dist + 2 * tree[h].down_nodes + 1) + tree[p].upDist + tree[p].up_nodes;
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<Node> tree(n);
	for (int i = 0; i < n - 1; ++i)
	{
		int par, child;
		std::cin >> par >> child;
		tree[par].childs.push_back(child);
		tree[child].parent = par;
	}
	countNodesDown(0, tree);
	for (int i = 1; i < n; ++i)
		countNodesUp(i, tree);
	findDownDist(0, tree);
	for (int i = 1; i < n; ++i)
		findUpDist(i, tree);
        
	for (int i = 0; i < n; ++i)
	{
		std::cout << tree[i].down_dist + tree[i].upDist << " ";
		//std::cout << tree[i].upDist << " ";
	}
	
}