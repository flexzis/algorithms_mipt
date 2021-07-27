/*
Task: Для сложения чисел используется старый компьютер.
Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11
Требуется написать программу, которая определяет минимальное время,
достаточное для вычисления суммы заданного набора чисел. Требуемое время работы O(n*log(n)).
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int time_needed(std::vector<int> v)
{
	std::make_heap(v.begin(), v.end(), [](int a, int b) { return a > b; });
	int sum = 0;
	while (v.size() > 1)
	{
		std::pop_heap(v.begin(), v.end(), [](int a, int b) { return a > b; });
		int s1 = v.back();
		v.pop_back();
		std::pop_heap(v.begin(), v.end(), [](int a, int b) { return a > b; });
		int s2 = v.back();
		v.pop_back();
		sum += s1 + s2;
		v.push_back(s1 + s2);
		std::make_heap(v.begin(), v.end(), [](int a, int b) { return a > b; });
	}
	return sum;
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> v(n);
	for (int i = 0; i < n; std::cin >> v[i++]);
	std::cout << time_needed(v);
}
