/*
Task: В круг выстроено N человек, пронумерованных числами от 1 до N.
Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й,
затем 2-й, затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й.
Таким образом, уцелеет 4-й.
Необходимо определить номер уцелевшего.
N, k ≤ 10000.
*/
#include <iostream>

int survived(int n, int k)
 {
	int person_index = 0;
	for (int i = 1; i <= n; ++i)
		person_index = (person_index + k) % i;
	return ++person_index;
}

int main()
{

	int n;
	int k;
	std::cin >> n;
	std::cin >> k;
	std::cout << survived(n, k);
}