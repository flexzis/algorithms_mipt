/*
Task: Вывести разложение натурального числа n на простые множители.
Простые множители должны быть упорядочены по возрастанию и разделены пробелами. 2 ≤ n ≤ 106.
*/
#include <iostream>
#include <vector>


std::vector<int> prime_factor(int n)
{
	std::vector<int> res;
	if (n < 2)
	{
		res.push_back(1);
		return res;
	}

	for (; n % 2 == 0; n /= 2)
		res.push_back(2);

	for (int i = 3; i * i <= n; i += 2) //i*i ~ danger
	{
		for (; n % i == 0; n /= i)
			res.push_back(i);
	}
	if (n > 1)
		res.push_back(n);

	return res;
}
int main()
{
	int n;
	std::cin >> n;
	std::vector<int> ans = prime_factor(n);
	for (auto x : ans)
		std::cout << x << " ";
}