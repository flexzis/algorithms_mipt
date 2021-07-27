#pragma once
//1_5. База данных

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Record
{
	std::string name;
	std::vector<int> data;
};


class Comp_permutations
{
	std::vector<int> priority;
public:
	Comp_permutations(const std::vector<int>& a) : priority{ a } { }

	bool operator ()(const Record& a, const Record& b)
	{
		for (int i = 0; i < priority.size(); ++i)
		{
			if (a.data[priority[i]] < b.data[priority[i]])
				return false;
			else if (a.data[priority[i]] > b.data[priority[i]])
				return true;
		}
		return false;
	}
};

int main()
{
	int n;
	std::cin >> n;
	int k;
	std::cin >> k;
	std::vector<int> prior(k);

	for (int i = 0; i < k; i++)
	{
		int tmp;
		std::cin >> tmp;
		prior[i] = tmp - 1;
	}

	std::vector<Record> records(n);

	for (int i = 0; i < n; ++i)
	{
		char c;
		std::cin >> c;
		while (!isalpha(c))
		{
			records[i].name.push_back(c);
			std::cin >> c;
		}
		std::cin.putback(c);
		std::cin >> records[i].name;
		records[i].data.resize(k);

		for (int j = 0; j < k; std::cin >> records[i].data[j++]);
	}

	Comp_permutations cmp(prior);
	std::sort(records.begin(),records.end(), cmp);

	for (auto& x : records)
		std::cout << x.name << std::endl;
}
