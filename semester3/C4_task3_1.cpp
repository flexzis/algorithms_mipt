#include <iostream>
#include <vector>

int main()
{
    uint64_t num;
    std::cin >> num;
    std::vector<std::vector<uint64_t>> a(num + 1, std::vector<uint64_t>(num + 1, 0));
    for (auto i = 0; i <= num; ++i)
    {
        a[1][i] = 1;
    }
    
    for(auto i = 2; i <= num; i++)
        for(auto j = 0; j <= num; j++)
            a[i][j] = a[i - 1][j] + ((j + 1 > i) ? (a[i][j - i]) : 0);

    std::cout << a[num][num];
}