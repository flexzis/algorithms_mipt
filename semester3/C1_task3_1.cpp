/*
Task: Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс k минимального
элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
Если такого элемента нет, выведите n.
Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
*/
#include <iostream>
#include <vector>

int find_elem(const std::vector<int>& a, int value)
{
	if (!a.size())
		return -1;
	if (value > a.back())
		return a.size();
	int ind = 1;
	while (ind < a.size() and a[ind] < value)
		ind *= 2;
	//по идее, надо сейчас использовать бинарный поиск, но...(
	for (int i = ind / 2; i <= ind; ++i)
	{
		if (a[i] >= value)
		{
			ind = i;
			break;
		}
	}
	return ind;
}

int main()
{
	int n;
	std::cin >> n;

	std::vector<int> sorted(n);
	std::cin >> n;
	std::vector<int> v(n);
	std::cin.get();
	for (int i = 0; i < sorted.size(); std::cin >> sorted[i++]);
	std::cin.get();
	for (int i = 0; i < v.size(); std::cin >> v[i++]);
	
	for (auto x : v)
		std::cout << find_elem(sorted, x) << " ";
	std::cout << std::endl;

}