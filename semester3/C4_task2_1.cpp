#include <iostream>
#include <vector>
#include <algorithm>

using atlet = std::pair<uint32_t, uint32_t>;

int pyramide_height(const std::vector<atlet>& a)
{
    if (a.empty())
        return 0;

    int h = 1;
    uint64_t totalWeight = a.front().first;

    for (auto i = 1; i < a.size(); ++i)
    {
        if (a[i].second >= totalWeight)
        {
            totalWeight += a[i].first;
            ++h;
        }
    }
    return h;
}

int main ()
{
    std::vector<atlet> a;
    a.reserve(100);
    atlet t;

    while (std::cin >> t.first >> t.second)
        a.push_back(t);
    
    std::sort(a.begin(), a.end(), [] (const atlet& lhs, const atlet& rhs)
    {return lhs.second < rhs.second;});
    
    std::cout << pyramide_height(a);
}