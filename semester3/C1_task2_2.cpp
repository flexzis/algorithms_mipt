/*
Task: Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
Вначале вводится количество вершин,
затем последовательно целочисленные координаты всех вершин в порядке обхода по часовой стрелке.

n < 1000, координаты < 10000.
*/
#include <iostream>
#include <vector>
struct point
{
	int x;
	int y;
};
double square(const std::vector<point>& p)
{
	if (p.size() < 3)
		return 0;
	double s = 0;

	for (int i = 0; i < p.size() - 1; ++i)
			s += (p[i].x - p[i + 1].x) * (p[i].y + p[i + 1].y);

	s += (p.back().x - p.front().x) * (p.back().y + p.front().y);
	return abs(s) / 2.;
}
int main()
{
	int n;
	std::cin >> n;
	std::vector<point> points(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> points[i].x;
		std::cin >> points[i].y;
	}
	std::cout << square(points);

}