/*
Task: Дана последовательность N прямоугольников различной ширины и высоты (wi, hi).
Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо).
Требуется найти M - площадь максимального прямоугольника (параллельного осям координат),
который можно вырезать из этой фигуры.
Время работы - O(n).
*/
#include <iostream>
#include <vector>
#include <stack>

struct rectangle
{
	int x1, x2, h;
	rectangle(int x1, int x2, int h):
		x1{ x1 }
		, x2 { x2 }
		, h { h }
	{ }
};

int main()
{
	int n;
	std::cin >> n;
	std::stack<rectangle> stq;
	int cur_x = 0;
	int maxS = 0;
	for (int i = 0; i < n; ++i)
	{
		int w, h;
		std::cin >> w >> h;
		//current rectangle higher than "~previous" (in stack)
		while (!stq.empty() && h < stq.top().h)
		{
			int s = stq.top().h * (cur_x - stq.top().x1);
			if (maxS < s)
				maxS = s;
			stq.pop();
		}
		stq.push(rectangle ((stq.empty() ? 0 : stq.top().x2), cur_x + w, h));
	//	std::cout << "  : " << stq.top().h << std::endl;
		cur_x += w;
	}
	while (!stq.empty())
	{
		int s = stq.top().h * (cur_x - stq.top().x1);
		if (maxS < s)
			maxS = s;
		stq.pop();
	}
	std::cout << maxS;
}



