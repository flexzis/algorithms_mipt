/*
Task: Найти, на сколько нулей оканчивается n! = 1 * 2 * 3 * … * n. n ≤ 1000.
*/
#include <iostream>
int zero_in_fact(int n)
{
	int res{ 0 };
	for (; n != 0; n /= 5, res += n);
	return res;
}

int main()
{
	int n;
	std::cin >> n;
	std::cout << zero_in_fact(n);
}