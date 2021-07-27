/*
Task: Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
Найти количество таких пар индексов (i, j), что A[i] + B[j] = k.
Время работы O(n + m). n, m ≤ 100000.
*/
#include <iostream>
#include <vector>

int sum_pairs(const std::vector<int>& v1, const std::vector<int>& v2, int sum)
{
	if (!v1.size() or !v2.size())
		return 0;
	int i0 = 0;
	int j0 = v2.size() - 1;
	int pairs = 0;
	while (i0 != v1.size() and j0 >= 0)
	{
		int loc_sum = v1[i0] + v2[j0];
		if (loc_sum < sum)
			i0++;
		else if (loc_sum > sum)
			j0--;
		else
		{
			pairs++;
			j0--;
		}
	}
	return pairs;
}

int main()
{
	int n;

	std::cin >> n;
	std::vector<int> v1(n);
	for (int i = 0; i < n; v1[i++])

	std::cin >> n;
	std::vector<int> v2(n);
	for (int i = 0; i < n; v2[i++])

	int sum ;
	std::cin >> sum;

	std::cout << sum_pairs(v1, v2, sum);
}