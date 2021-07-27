//4_1. Первые k элементов длинной последовательности

//я без понятия как здесь адекватно использовать merge

#include <iostream>
#include <vector>
#include <algorithm>
template <class T>
void InsertionSort(std::vector<T>& v)
{
	if (v.size() <= 1)
		return;
	for (int i = 1; i < v.size(); ++i)
	{
		for (int j = i - 1; j >= 0 and v[j] > v[j + 1]; --j)
			std::swap(v[j], v[j + 1]);
	}
}

void PutInCorrectPos(std::vector<int>& v, int new_el)
{
	if (new_el > v.back())
		return;
	int new_elem_ind = 0;
	for (; new_elem_ind < v.size() and v[new_elem_ind] < new_el; ++new_elem_ind);
	for (int i = v.size() - 1; i > new_elem_ind; --i)
	{
		v[i] = v[i - 1];
	}
	v[new_elem_ind] = new_el;
}


int main()
{
	int n, k;
	std::cin >> n >> k;
	std::vector<int> res(k);
	for (int i = 0; i < k; std::cin >>res[i++]);
	InsertionSort(res);
	int t;
	while (std::cin >> t)
	{
		PutInCorrectPos(res, t);
	}
	for (auto x : res)
		std::cout << x << " ";
}