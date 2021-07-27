//5_2. LSD для long long

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

template <typename T>
int get_byte(T number, size_t n)
{
	return number >> (8 * n) & 255;
}


template <class T>
void stable_count_sort(std::vector<T>& arr, size_t byte, int lower_bound = 0,
	int upper_bound = 256)
{
	if (arr.size() <= 1)
		return;
	std::vector<T> auxiliary(upper_bound - lower_bound + 1, 0);
	for (auto x : arr)
	{
		++auxiliary[get_byte(x, byte) - lower_bound];
	}
	for (int i = 1; i < auxiliary.size(); ++i)
	{
		auxiliary[i] += auxiliary[i - 1];
	}
	std::vector<T>sorted(arr.size());
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		sorted[--auxiliary[get_byte(arr[i], byte) - lower_bound]] = arr[i];
	}
	arr = sorted;
}


template <class T>
void LSD_sort(std::vector<T>& arr, int lower_bound = 0,
	int upper_bound = sizeof(T))
{
	for (int digit = lower_bound; digit < upper_bound; ++digit)
	{
		stable_count_sort(arr, digit);
	}
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<long long> a(n);
	for (int i = 0; i < n; std::cin >> a[i++]);
	LSD_sort(a);
	for (auto& x : a)
		std::cout << x << " ";
}