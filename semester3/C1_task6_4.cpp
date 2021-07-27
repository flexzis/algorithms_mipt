/*
Task: Дан массив целых чисел A[0..n), n не превосходит 100 000.
Так же задан размер некотрого окна (последовательно расположенных элементов массива) в этом массиве k,
k<=n. Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне.
Скорость работы O(n log n), память O(n).
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> A(n);
	for (int i = 0; i < n; std::cin >> A[i++]);
	if (n == 1)
	{
		std::cout << A.back();
		return 0;
	}
	int k;
	std::cin >> k;
	if (k == 1)
	{
		for (auto x : A)
			std::cout << x << " ";
		return 0;
	}
	std::vector<int> B(n);
	std::vector<int> C(n);
	for (int i = 0; i < n; i++)
	{
		if (i % k)
			B[i] = std::max(A[i], B[i - 1]);
		else
			B[i] = A[i];
	}
	C.back() = A.back();
	for (int i = n - 2; i >= 0; i--)
	{
		if ((i + 1) % k)
			C[i] = std::max(A[i], C[i + 1]);
		else
			C[i] = A[i];
	}
	for (int i = 0; i <= n - k; i++)
	{
		std::cout << std::max(B[i + k - 1], C[i]) << " ";
	}
}

