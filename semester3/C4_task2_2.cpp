#include <iostream>
#include <vector>
#include <algorithm>

using period = std::pair<int, int>; 

int max_requests(const std::vector<period>& a)
{
    if (a.empty())
        return 0;

    int requests = 1;
    period cur = a[0];
    for (auto i = 1; i < a.size(); ++i)
    {
        if (a[i].first < cur.second && a[i].second <= cur.second)
            cur = a[i];
        else if (a[i].first >= cur.second)
        {
            ++requests;
            cur = a[i];
        }
    }
    return requests;
}

int main ()
{
    std::vector<period> a;
    period t;
    while (std::cin >> t.first >> t.second)
        a.push_back(t);
    std::sort(a.begin(), a.end(), [](const period& lhs, const period& rhs)
    {return lhs.first < rhs.first;});
    std::cout << max_requests(a);
}