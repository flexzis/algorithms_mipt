//7. Быстрейшая сортировка
#include <iostream>
#include <vector>
#include <random>
#include <cstdint>

//std::random_device rand_machine;
//std::mt19937 generator(rand_machine());

template <class Iter>
void InsertionSort(Iter begin, Iter end)
{
	if (end - begin < 2)
		return;
	for (auto i = begin + 1; i < end; ++i)
	{
		for (auto j = i - 1; j >= begin and *(j + 1) < *(j);)
		{
			std::swap(*j, *(j + 1));
			if (j != begin) --j;
		}
	}
}

//template <typename Iter>
//Iter pivot(Iter begin, Iter end)
//{
//	std::uniform_int_distribution<size_t> distribution(0, end - begin - 1);
//	return begin + distribution(generator);
//}

template <typename Iter>
Iter med(const Iter a, const Iter b, const Iter c)
{
	if (*a > *b)
	{
		if (*c > *a)
			return a;
		return (*b > *c) ? b : c;
	}

	if (*c > *b)
		return b;

	return (*a > *c) ? a : c;
}


template <typename Iter>
Iter partit(Iter begin, Iter end)
{
	auto p = med(begin, (begin + (end - begin) / 2), end);
	auto pivot = *p;
	std::swap(*p, *(end - 1));
	--end;
	auto i = begin, j = end - 1;

	while (i <j)
	{
		while (i != end and *i < pivot)
			++i;
		while (j != begin and !(*j < pivot))
			--j;
		if (i < j)
			std::swap(*i, *j);
	}
	std::swap(*end, *i);

	return i;
}

template <typename Iter>
void quick_sort(Iter begin, Iter end)
{
	while (end - begin > 50)
	{
		Iter p = partit(begin, end);
		if (p - begin < end - p + 1)
		{
			quick_sort(begin, p);
			begin = p + 1;
		}
		else
		{
			quick_sort(p + 1, end);
			end = p;
		}
	}
	InsertionSort(begin, end);
}

int main()
{
	//test();
	std::ios::sync_with_stdio(false);
	std::vector<uint32_t> a;
	a.reserve(25000000);
	while (std::cin.good())
	{
		uint32_t tmp;
		std::cin >> tmp;
		a.push_back(tmp);
	}
	quick_sort(a.begin(), a.end() - 1);
	for (auto i = 9; i < a.size() - 1; i += 10)
		std::cout << a[i] << ' ';

}