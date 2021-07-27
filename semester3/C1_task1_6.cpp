/*
Task: Дан массив целых чисел A[0..n).
 Не используя других массивов переставить элементы массива A в обратном порядке за O(n). n ≤ 10000.
*/
#include <iostream>
#include <vector>

void my_reverse(std::vector<int>& v)
{
	if (v.size() < 2)
		return;
	for (int i = 0; i < v.size() / 2; ++i)
	{
		std::swap(v[i], v[v.size() - (i + 1)]);
	}
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; std::cin >> a[i++]);
	my_reverse(a);
	for (auto x : a)
		std::cout << x << " ";
}