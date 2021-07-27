#include <iostream>
#include <stack>
#include <queue>

template <typename T, typename Cmp = std::less<>>
class BinaryTree
{
    template <typename T>
    struct Node
    {
	    T key;
	    Node() = default;
	    explicit Node(const T& value)
		    : key{ value }
    	{ }
        Node<T>* parent = nullptr;
	    Node<T>* left = nullptr;
	    Node<T>* right = nullptr;
	    ~Node()
	    {
	    	delete left;
	    	delete right;
	    }
};
	Node<T>* root = nullptr;
	Cmp comp{};
public:
	BinaryTree() = default;
	explicit BinaryTree(const T& key)
		: root{ new Node<T>(key) }
	{ }
	void add(const T& key);
	void inOrderPrint() const;
	void preOrderPrint() const;
	void pastOrderPrint() const;
	void levelOrderPrint() const;
	~BinaryTree()
	{
		delete root;
	}
};

template <typename T, typename Cmp>
void BinaryTree<T, Cmp>::add(const T & key)
{
	Node<T>* newNode = new Node<T>;
	newNode->key = key;

	if (!root)
	{
		root = newNode;
		return;
	}
	Node<T>* findPlaceNode = root;
	while (findPlaceNode)
	{
		if (comp(key, findPlaceNode->key))
		{
			if (!findPlaceNode->left)
			{
				findPlaceNode->left = newNode;
				return;
			}
			findPlaceNode = findPlaceNode->left;
		}
		else
		{
			if (!findPlaceNode->right)
			{
				findPlaceNode->right = newNode;
				return;
			}
			findPlaceNode = findPlaceNode->right;
		}
	}
	return;
}

template <typename T, class Cmp>
void  BinaryTree<T, Cmp>::inOrderPrint() const
{
	std::stack<Node<T>*> s;
	Node<T>* curNode = root;
	while (!s.empty() or curNode)
	{
		if (curNode)
		{
			s.push(curNode);
			curNode = curNode->left;
		}
		else
		{
			curNode = s.top();
			s.pop();
			std::cout << curNode->key << " "; //!!
			curNode = curNode->right;
		}
	}
	return;
}
template <typename T, class Cmp>
void  BinaryTree<T, Cmp>::preOrderPrint() const
{
	if (!root)
		return;
	std::stack<Node<T>*> s;
	s.push(root);
	while (!s.empty())
	{
		Node<T>* curNode = s.top();
		s.pop();
		std::cout << curNode->key << " ";
		if (curNode->right)
			s.push(curNode->right);
		if (curNode->left)
			s.push(curNode->left);
	}
	return;
}
template <typename T, class Cmp>
void  BinaryTree<T, Cmp>::pastOrderPrint() const
{
	if (!root)
		return;
	std::stack<Node<T>*> s;
	Node<T>* curNode = root;
	Node<T>* lastVisitedNode = nullptr;
	while (!s.empty() or curNode)
	{
		if (curNode)
		{
			s.push(curNode);
			curNode = curNode->left;
		}
		else
		{
			Node<T>* topStackNode = s.top();
			if (topStackNode->right and lastVisitedNode != topStackNode->right)
				curNode = topStackNode->right;
			else
			{
				std::cout << topStackNode->key << " "; //!!
				lastVisitedNode = s.top();
				s.pop();
			}
		}
	}
	return;
}

template <typename T, class Cmp>
void  BinaryTree<T, Cmp>::levelOrderPrint() const
{
	if (!root)
		return;
	std::queue<Node<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		Node<T>* curNode = q.front();
		q.pop();
		std::cout << curNode->key << " ";
		if (curNode->left)
			q.push(curNode->left);
		if (curNode->right)
			q.push(curNode->right);
	}
}

int main()
{
	BinaryTree<int> tree;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		std::cin >> tmp;
		tree.add(tmp);
	}
	tree.levelOrderPrint();
}
