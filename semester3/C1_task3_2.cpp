/*
Task: Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m]
значения массива строго возрастают,
а на интервале [m, n-1] строго убывают. Найти m за O( log m ).
2 ≤ n ≤ 10000.
*/
#include <iostream>
#include <vector>
int find_elem(std::vector<int>& a)
{
	if (!a.size())
		return -1;
	int i0 = 0;
	for (int i = 1; i < a.size() and a[i] > a[i0]; i0 = i, i *= 2);
	//по идее, надо сейчас использовать бинарный поиск, но...(
	int m;
	for (m = i0; i0 < a.size() - 1; ++m)
		if (a[m] > a[++i0])
			break;
	return m;
}

int main()
{
	int n;
	std::cin >> n;

	std::vector<int> v(n);
	for (int i = 0; i < n; std::cin >> v[i++]);
	std::cout << find_elem(v);
}