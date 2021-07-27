/*
Task: Дано натуральное число N. Представить N в виде A + B, так,
что НОД(A, B) максимален, 1 ≤ A ≤ B. Вывести A и B.
Если возможно несколько ответов - вывести ответ с минимальным A. 1 < n ≤ 10 000 000.
*/
#include <iostream>

int min_den(int n)
{
	if (n == 1)
		return 1;
	if (n % 2 == 0)
		return 2;
	for (int i = 3; i * i <= n; i += 2)
	{
		if (n % i == 0)
			return i;
	}
	return n;
}

std::pair<int, int>max_gcd_sum(int n)
{
	if (n == 1)
		return { 0 , 1 };
	int res = n / min_den(n);
	if (res == 0)
		return { 1, n - 1};
	return { res, n - res };
}

int main()
{
	int n;
	std::cin >> n;
	std::pair<int, int> ans = max_gcd_sum(n);
	std::cout << ans.first << " " << ans.second;
}