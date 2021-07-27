//1_3. Замкнутая ломаная

#include <iostream>
#include <vector>
#include <cmath>
template <class T, class Compare>
void InsertionSort(std::vector<T>& v, Compare comp)
{
	if (v.size() <= 1)
		return;
	for (int i = 1; i < v.size(); ++i)
	{
		for (int j = i - 1; j >= 1 and comp(v[j + 1], v[j]); --j)
			std::swap(v[j], v[j + 1]);
	}
}

struct point
{
public:
	int x;
	int y;
	double angle;
	point() : x{ 0 }, y{ 0 }, angle{ 0 } { }
	point(const point& a) : x{ a.x }, y{ a.y }, angle{ a.angle } { }
	point& operator = (const point& a)
	{
		x = a.x;
		y = a.y;
		angle = a.angle;
		return *this;
	}
	bool operator == (const point& a) const
	{
		return x == a.x and y == a.y;
	}
};
void putMinFirst(std::vector<point>& v)
{
	point m = v[0];
	int min_ind = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if (m.x > v[i].x or m.x == v[i].x and m.y > v[i].y)
		{
			m.x = v[i].x;
			m.y = v[i].y;
			min_ind = i;
		}
	}
	std::swap(v[0].y, v[min_ind].y);
	std::swap(v[0].x, v[min_ind].x);
}
void putAngles(std::vector<point>& in)
{
	for (auto& a : in)
	{
		if (a.x == in[0].x)
			a.angle = 2;
		else
		{
			a.angle = atan2(a.y - in[0].y, a.x - in[0].x);
		}
	}
}
int main()
{
	int n;
	std::cin >> n;
	std::vector<point> v (n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> v[i].x;
		std::cin >> v[i].y;
	}
	putMinFirst(v);
	putAngles(v);
	InsertionSort(v, [](const point& x1, const point& x2)
		{return x1.angle > x2.angle; });
	for (auto& a : v)
		std::cout << a.x << " " << a.y << std::endl;
}
