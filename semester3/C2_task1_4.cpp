//1_4. Строки

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
template <class T, class Compare>
void InsertionSort(std::vector<T>& v, Compare comp)
{
	if (v.size() <= 1)
		return;
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = i - 1; j >= 0 and comp(v[j + 1], v[j]); --j)
			std::swap(v[j], v[j + 1]);
	}
}

bool strCmpLess(const std::string& s1, const std::string& s2)
{
	for (int i = 0; i < s1.size(); ++i)
	{
		if (i == s2.size())
			break;
		if (s1[i] < s2[i])
			return true;
		else if (s1[i] > s2[i])
			return false;
	}
	return s1.length() < s2.length();
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<std::string> v (n);
	std::cin.get();
	for (int i = 0; i < n; ++i)
	{
		std::getline(std::cin, v[i]);
	}
	//std::vector<std::string> test = v;
	//std::sort(test.begin(), test.end());
	InsertionSort(v, strCmpLess);
	for (auto& a : v)
		std::cout << a << std::endl;
}
