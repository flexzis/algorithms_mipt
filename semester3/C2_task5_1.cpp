#include <iostream>
#include <vector>
#include <cstdint>

bool bit_val(long long number, int position)
{
	return (number >> position) & 1;
}

void quicksortBin(std::vector<long long>& a, int l, int r, int bit_n)
{
	if (r <= l || bit_n < 0)
		return;

	int i = l, j = r;

	while (i < j)
	{
		while (i != j and !bit_val(a[i], bit_n))
			i++;

		while (j != i and bit_val(a[j], bit_n))
			j--;

		std::swap(a[i], a[j]);	

	}
	if (bit_val(a[r], bit_n) == 0)
		j++;

	quicksortBin(a, l, j - 1, bit_n - 1);
	quicksortBin(a, j, r, bit_n - 1);
}

int main()
{
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	std::vector<long long> a(n);
	
	for (int i = 0; i < n; std::cin >> a[i++]);

	quicksortBin(a, 0, n - 1, 63);
	for (auto x : a)
		std::cout << x << ' ';
}
