/*
Task: Даны четыре неотрицательных числа a, b, c и d.
 Сложить две рациональные дроби a/b и c/d,
а их результат представить в виде несократимой дроби m/n.
Вывести числа m и n. a, b, c, d ≤ 1000.
*/
#include <iostream>

int gcd(int a, int b)
{
	if (a == b)
		return a;
	if (b > a)
		std::swap(a, b);
	while (a != b and b != 0)
	{
		a %= b;
		std::swap(a, b);
	}
	return a;
}

std::pair<int,int> fraction_sum(int n1, int d1, int n2, int d2) 
{
	//(n1/d1) + (n2/d2) = (n1d1+n2d2)/(d1d2)
	int div = gcd(d1, d2);
	int num = d2 / div * n1 + d1 / div * n2;
	int den = d1 / div * d2;
	div = gcd(num, den);
	return { num / div, den / div};
}

int main()
{
	int a, b, c, d;
	std::cin >> a >> b >> c >> d;
	std::pair<int, int> ans = fraction_sum(a, b, c, d);
	std::cout << ans.first << " " << ans.second;
}