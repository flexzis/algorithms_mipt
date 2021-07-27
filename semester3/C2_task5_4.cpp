//5_4. Очень быстрая сортировка

#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <cstring>

template <typename T>
inline int get_byte(T number, size_t n)
{
	return number >> (8 * n) & 255;
}

template <class T>
void stable_count_sort(std::vector<T>& arr, size_t byte, int lower_bound = 0,
	int upper_bound = 256)
{
	if (arr.size() <= 1)
		return;
	std::vector<T> ends_indexes(upper_bound - lower_bound + 1, 0);
	for (auto& x : arr)
	{
		++ends_indexes[get_byte(x, byte) - lower_bound];
	}
	for (int i = 1; i < ends_indexes.size(); ++i)
	{
		ends_indexes[i] += ends_indexes[i - 1];
	}
	std::vector<T>sorted(arr.size());
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		int ind = --ends_indexes[get_byte(arr[i], byte) - lower_bound];
		sorted[ind] = arr[i];
	}
	arr = sorted;
}
template <class T>
void LSD_sort(std::vector<T>& arr, int lower_bound = 0,
	int upper_bound = sizeof(T))
{
	for (int n_byte = lower_bound; n_byte < upper_bound; ++n_byte)
	{
		stable_count_sort(arr, n_byte);
	}
}
int main() {

	std::ios::sync_with_stdio(false);

	unsigned n, k, m, l;

	std::cin >> n >> k >> m >> l;

	std::vector<unsigned > a(n);

	a[0] = k;

	for (unsigned i = 1; i < n; ++i) {
		a[i] = unsigned(((uint_fast64_t(a[i - 1]) * m) & 0xFFFFFFFFU)) % l;
	}

	LSD_sort(a);

	uint_fast64_t sum{ 0 };

	for (unsigned i = 0; i < n; i += 2)
		sum += a[i];

	std::cout << sum % l;
}