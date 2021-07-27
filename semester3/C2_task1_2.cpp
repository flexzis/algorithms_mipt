//1_2. Ломаная 1

#include <iostream>
#include <vector>
#include <algorithm>

struct Point
{
	int x;
	int y;
	int number;
    
	bool operator < (const Point& a)
	{
		return x != a.x ? x < a.x : y < a.y;
	}
};

int main()
{
	int n;
	std::cin >> n;
	std::vector<Point> v (n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> v[i].x;
		std::cin >> v[i].y;
	}
	std::sort(v.begin(), v.end());
	for (auto& a : v)
		std::cout << a.x << " " << a.y << std::endl;
}
