//3. Порядковая статистика

#include <iostream>
#include <vector>
#include <random>

std::random_device random_device; 
std::mt19937 generator(random_device());
template <typename Iter>
Iter pivot(Iter begin, Iter end)
{
	std::uniform_int_distribution<size_t> distribution(0, end - begin - 1);
	return begin + distribution(generator);
}

template <typename Iter>
Iter partition(Iter begin, Iter end)
{
	auto p = pivot(begin, end);
	auto pivot = *p;
	std::swap(*p, *(end - 1));
	auto i = begin, j = end - 1;

	while (i < j) {
		while (i != end - 1 and *i < pivot)
			++i;
		while (j != begin and *j >= pivot)
			--j;

		if (i < j)
			std::swap(*i, *j);
	}

	std::swap(*(end - 1), *i);

	return i;
}

template <typename Iter>
Iter randomized_select(Iter begin, Iter end, Iter position)
{
	if (end - begin <= 1)
		return begin;
	while (begin != end)
	{
		auto pivot = partition(begin, end);
		if (position == pivot)
			return pivot;
		if (position > pivot)
			begin = pivot;
		else
			end = pivot;
	}
	return position;
}


int main() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> v(n);
	for (int i = 0; i < n; std::cin >> v[i++]);
	std::cout << *randomized_select(v.begin(), v.end(), v.begin() + k);
}
