/*
Task: Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 Необходимо найти первую пару индексов i0 и j0,
 такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
  Время работы - O(n). n ≤ 100000.
*/
#include <iostream>
#include <vector>

std::pair<int, int> min_sum_ind(std::vector<int>& v1, std::vector<int>& v2)
{

	if (v1.size() <= 1)
		return { 0, 0 };
	int i1 = 0;
	int i2 = 0;
	int loc_max_v1_ind = 0;
	for (int k = 0; k < v1.size(); ++k)
	{
		if (v1[k] > v1[loc_max_v1_ind])
		{
			loc_max_v1_ind = k;

		}
		if (v2[k] + v1[loc_max_v1_ind] > v1[i1] + v2[i2])
		{
			i1 = loc_max_v1_ind;
			i2 = k;
		}
	}
	return { i1, i2 };
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> a1(n);
	std::vector<int> a2(n);

	for (int i = 0; i < n; std::cin >> a1[i++]);
	for (int i = 0; i < n; std::cin >> a2[i++]);

	std::pair<int, int> ans = min_sum_ind(a1, a2);
	std::cout << ans.first << " " << ans.second;
}