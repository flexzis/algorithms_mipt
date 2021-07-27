#include <iostream>
#include <vector>

int main()
{
    uint64_t num;
    std::cin >> num;
    std::vector<std::vector<uint64_t>> a(num + 1, std::vector<uint64_t>(num + 1, 0));
    for (auto i = 0; i <= num; ++i)
    {
        a[0][i] = 1;
        a[1][i] = 1;
    }
    for (auto i = 2; i <= num; ++i)
        for (auto j = 2; j <= num; ++j)
            a[i][j] = (j <= i ? a[i - j][j - 1] + a[i][j - 1] : a[i][j - 1]);

    std::cout << a[num][num];
}   