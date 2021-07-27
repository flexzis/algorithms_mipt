/*
Task: Вовочка ест фрукты из бабушкиной корзины.
В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм.
Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов,
которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину.
Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.

Определить за сколько подходов Вовочка съест все фрукты в корзине.
*/
#include <iostream>
#include <vector>
#include <algorithm>

int number_of_approaches(std::vector<int>& fruits, int k)
{
	std::make_heap(fruits.begin(), fruits.end());
	int res = 0;
	int sum = 0;
	std::vector<int> taken_fruits;
	while (!fruits.empty())
	{
		std::pop_heap(fruits.begin(), fruits.end());
		auto heavy_fruit = fruits.back();
		sum += heavy_fruit;
		if (sum > k or fruits.size() == 1)
		{
			if (sum > k)
             //put back excess fruit
				std::push_heap(fruits.begin(), fruits.end());
			else
			{
				taken_fruits.push_back(heavy_fruit);
				fruits.pop_back();
			}
			while (!taken_fruits.empty())
			{
				if (taken_fruits.back() > 1)
				{
					fruits.push_back(taken_fruits.back() / 2);
					std::push_heap(fruits.begin(), fruits.end());
				}
				taken_fruits.pop_back();
			}
			++res;
			sum = 0;
		}
		else
		{
			fruits.pop_back();
			taken_fruits.push_back(heavy_fruit);
		}
	}
	if (!taken_fruits.empty())
		++res;

	return res;
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> fruits(n);
	for (int i = 0; i < n; std::cin >> fruits[i++]);
	int k;
	std::cin >> k;
	std::cout << number_of_approaches(fruits, k);
}
