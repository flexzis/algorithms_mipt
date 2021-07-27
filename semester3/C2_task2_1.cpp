//2_1. Реклама

#include <iostream>
#include <vector>
#include <algorithm>

struct Buyer
{
	int t1;
	int t2;
	int ads_seen;
	Buyer() : t1{ 0 }, t2{ 0 }, ads_seen{ 0 } { }
	Buyer(int arrived_time, int leaved_time)
		: t1{ arrived_time }, t2{ leaved_time }, ads_seen { 0 }
	{}
};

bool operator<(const Buyer &a, const Buyer &b)
{
    if (a.t2 < b.t2)
        return true;
        
    return a.t2 == b.t2 && a.t1 > b.t1;
}

int adsNeeded(std::vector<Buyer>& a)
{
	if (a.empty())
		return 0;

	int total_ads = 0;

	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i].ads_seen == 0)
		{
			for (int j = i - 1; ++j < a.size() && a[i].t2 > a[j].t1;)
			{
				++a[j].ads_seen;
			}
			++total_ads;
		}

		if (a[i].ads_seen == 1)
		{
			for (int j = i - 1; ++j < a.size() && a[i].t2 >= a[j].t1;)
			{
				++a[j].ads_seen;
			}
			++total_ads;
		}
	}
	return total_ads;
}


int main()
{
	int n;
	std::cin >> n;
	std::vector<Buyer> a(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> a[i].t1 >> a[i].t2;
	}
	std::sort(a.begin(), a.end());
	std::cout << adsNeeded(a);
}
