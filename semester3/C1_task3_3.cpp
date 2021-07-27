/*
Task: Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение. 
Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A..
В процессе поиска очередного элемента B[i] в массиве A
пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.
*/
#include <iostream>
#include <vector>

using iter = std::vector<int>::iterator;


int bin_search(std::vector<int>& v, int beg, int end, int val)
{
	if (end - beg < 0)
		return false; //out of range
	while (beg <= end)
	{
		int mid = beg + (end - beg) / 2;
		if (v[mid] == val)
			return mid;

		if (val < v[mid])
			end = mid - 1;
		else 
			beg = mid + 1;
	}
	return -1;
}


std::vector<int> intersection (std::vector<int>& v1, std::vector<int>& v2)
{
	std::vector<int> intersect;
	if (!v1.size() or !v2.size())
		return intersect;

	int beg_offset = 0;
	int i0 = 0;
	int d_bound = 0;
	int up_bound = 1;
	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[i] < v1[0])
			continue;

		if (v2[i] > v1.back())
			break;

		while (up_bound < v1.size() and v2[i] > v1[up_bound])
				up_bound *= 2;

		if (up_bound >= v1.size())
			up_bound = v1.size() - 1;

		int intersec_el = bin_search(v1, d_bound, up_bound, v2[i]);
		if (intersec_el != -1)
		{ 
			intersect.push_back(v2[i]);
			d_bound = intersec_el;
		}
	}
	return intersect;
}

int main()
{

	int n;

	std::cin >> n;
	std::vector<int> v1(n);
	std::cin.get();

	std::cin >> n;
	std::vector<int> v2(n);
	std::cin.get();

	for (int i = 0; i < v1.size(); std::cin >> v1[i++]);

	std::cin.get();

	for (int i = 0; i < v2.size(); std::cin >> v2[i++]);

	std::vector<int> res = intersection(v1, v2);

	for (auto x : res)
		std::cout << x << " ";
	std::cout << std::endl;
}