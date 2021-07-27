/*
Task: На вокзале есть некоторое количество тупиков, куда прибывают электрички.
Этот вокзал является их конечной станцией.
Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия,
а также время отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия.
Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
При этом если электричка из какого-то тупика отправилась в момент времени X,
то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку,
прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
Напишите программу, которая по данному расписанию определяет,
какое минимальное количество тупиков требуется для работы вокзала.
*/
#include <iostream>
#include <vector>
#include <algorithm>

struct shedule
{
	int time;
	bool is_leaving;
};

int stops_needed(const std::vector<shedule>& v)
{
	int sum = 0;
	int max = -1;
	for (auto& x : v)
	{
		if (x.is_leaving)
			--sum;
		else
			++sum;
		if (sum > max)
			max = sum;
	}
	return max;
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<shedule> v(2 * n);
	for (int i = 0; i < 2 * n; ++i)
	{
		std::cin >> v[i].time;
		i % 2 == 0 ? v[i].is_leaving = false : v[i].is_leaving = true;
	}
	std::sort(v.begin(), v.end(), [](shedule a, shedule b)
		{ return a.time == b.time ?
        a.is_leaving < b.is_leaving : a.time < b.time; });
	std::cout << stops_needed(v);
}
