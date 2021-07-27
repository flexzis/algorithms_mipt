//2_2. Современники

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Date
{
	int d = 0;
	int m = 0;
	int y = 0;
	bool is_birth = 0;

	Date() = default;

	Date(int day, int month, int year)
		: d{ day }, m{ month }, y{ year }
	{}

	bool operator ==(const Date& a) const
	{
		return d == a.d and m == a.m and y == a.y;
	}

	bool operator<(const Date& a) const
	{
		if (y == a.y)
		{
			if (m == a.m)
				return d < a.d;
			return m < a.m;
		}
		return y < a.y;
	}

	bool operator<=(const Date& a) const
	{
		if (y == a.y)
		{
			if (m == a.m)
				return d <= a.d;
			return m <= a.m;
		}
		return y <= a.y;
	}

	Date& operator-(const Date& a) const
	{
		Date tmp(d - a.d, m - a.m, y - a.y);
		return tmp;
	}
};

std::istream& operator>>(std::istream& is, Date& a)
{
	is >> a.d >> a.m >> a.y;
	return is;
}

int contemporaries(const std::vector<Date>& v)
{
	int sum = 0;
	int max = -1;
	for (auto& x : v)
	{
		if (x.is_birth)
			++sum;
		else
			--sum;
		if (sum > max)
			max = sum;
	}
	return max == 0 ? 1 : max;
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<Date> dates;
	for (int i = 0; i < n; ++i)
	{
		Date birth, death;
		birth.is_birth = 1;
		death.is_birth = 0;
		std::cin >> birth >> death;
		if (death.y - birth.y < 18 or
			(death.y - birth.y == 18 and birth.d == death.d and birth.m == death.m))
			continue;
		if (death.y - birth.y > 80)
		{
			death.y = birth.y + 80;
			death.m = birth.m;
			death.d = birth.d;
		}
		else if (death.y - birth.y == 80)
		{
			if (death.m > birth.m)
			{
				death.m = birth.m;
				death.d = birth.d;
			}
			else if (death.m == birth.m and death.d > birth.d)
			{
				death.d = birth.d;
			}
		}
		birth.y += 18;
		dates.push_back(birth);
		dates.push_back(death);
	}

	std::sort(dates.begin(), dates.end(), [](Date a, Date b) { return a < b; });
	std::cout << contemporaries(dates);
}
