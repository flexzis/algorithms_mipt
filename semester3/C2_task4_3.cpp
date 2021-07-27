//4_3. Количество инверсий

#include <iostream>
#include <vector>

int64_t invCount(std::vector<int64_t>& v, size_t first_ind, size_t last_ind)
{
	if (first_ind == last_ind)
		return 0;
	size_t midle = (first_ind + last_ind) / 2;
	int64_t res = invCount(v, first_ind, midle) + invCount(v, midle + 1, last_ind);

	std::vector<int64_t> v1(v.begin() + first_ind, v.begin() + midle + 1);
	std::vector<int64_t> v2(v.begin() + midle + 1, v.begin() + last_ind + 1);

	size_t i1 = 0, i2 = 0, i = first_ind;

	for (; i1 < v1.size() && i2 < v2.size(); ++i)
	{
		if (v1[i1] > v2[i2])
		{
			v[i] = v2[i2];
			res += v1.size() - i1;
			++i2;
		}
		else
		{
			v[i] = v1[i1];
			++i1;
		}
	}

	for (; i1 < v1.size(); ++i1, ++i)
		v[i] = v1[i1];

	for (; i2 < v2.size(); ++i2, ++i)
		v[i] = v2[i2];

	return res;
}

int main() {
	std::vector<int64_t> v;
	std::cin.peek();
	while (std::cin.peek() != EOF)
	{
		int64_t t;
		std::cin >> t;
		v.push_back(t);
	}
	v.pop_back();
	std::cout << invCount(v, 0, v.size() - 1);
}
