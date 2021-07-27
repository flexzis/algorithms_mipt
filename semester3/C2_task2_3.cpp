//2_3. Закраска прямой

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Segment
{
	int x;
	bool beg;
};

int colored(const std::vector<Segment>& v)
{
	int cond, l;
	cond = l = 0;
	for (int i = 0; i < v.size() - 1; ++i)
	{
		if (v[i].beg == true)
			cond++;
		else
			cond--;
		if (cond > 0)
			l += v[i + 1].x - v[i].x;
	}
	return l;
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<Segment> v(2 * n);
	for (int i = 0; i < v.size(); ++i)
	{
		std::cin >> v[i].x;
		if (i % 2 == 0)
			v[i].beg = true;
		else
			v[i].beg = false;
	}
	std::sort(v.begin(), v.end(), [](Segment a, Segment b) {return a.x < b.x; });
	std::cout << colored(v);
}
