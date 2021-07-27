#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

struct Box
{
public:
	std::vector<int> data {0, 0, 0};
	int number;
	bool operator < (const Box& a)
	{
		return data[0] < a.data[0] && data[1] < a.data[1] && data[2] < a.data[2];
	}
};

std::istream& operator >> (std::istream& is, Box& a)
{
    is >> a.data[0] >> a.data[1] >> a.data[2];
    std::sort(a.data.begin(), a.data.end());
    return is;
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<Box> v(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> v[i];
		v[i].number = i;
	}
	std::sort(v.begin(), v.end());
	for (auto& x : v)
		std::cout << x.number << " ";
}
