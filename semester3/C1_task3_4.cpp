/*
Task: Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.
Время работы поиска для каждого элемента B[i]: O(log(k)).
*/
#include <iostream>
#include <vector>

int bin_search(const std::vector<int>& v, int beg, int end, int val)
{
	if (end - beg < 0)
		return false; //out of range
	int mid = -1;
	while (beg <= end)
	{
		mid = beg + (end - beg) / 2;
		if (v[mid] == val)
			return mid;

		if (val < v[mid])
			end = mid - 1;
		else 
			beg = mid + 1;
	}
	return mid;
}


int find_twin_ind (const std::vector<int>& v1, int val)
{
	if (!v1.size())
		return -1;
	int up_bound = 1;
	while (up_bound < v1.size() and val > v1[up_bound])
			up_bound *= 2;

	if (up_bound >= v1.size())
		up_bound = v1.size() - 1;
	int twin_ind = bin_search(v1, 0, up_bound, val);
	while (twin_ind < v1.size() - 1 and abs(v1[twin_ind + 1] - val) < abs(v1[twin_ind] - val))
		twin_ind++;
	while (twin_ind > 0 and abs(v1[twin_ind - 1] - val) <= abs(v1[twin_ind] - val))
		twin_ind--;
	return twin_ind;
}

int main()
{
	int n;

	std::cin >> n;
	std::vector<int> v1(n);
	for (int i = 0; i < v1.size(); std::cin >> v1[i++]);

	std::cin >> n;
	std::vector<int> v2(n);
	for (int i = 0; i < v2.size(); std::cin >> v2[i++]);


	for (auto x : v2)
		std::cout << find_twin_ind(v1, x) << " ";
	std::cout << std::endl;
}