/*
Task: Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.
Время работы поиска для каждого элемента B[i]: O(log(k)).
*/
#include <iostream>
#include <vector>

template<class T>
class cycled_queue
{
	int head;
	int tail;
	int sz;
    std::vector<T> elem;
public:
	cycled_queue(int n) : sz{0}
	{
		elem.resize(n);
		head;
		tail;
	}

	void push_back(const T& val)
	{
		if (sz == elem.size())
			resize(2 * sz);
		if (sz == 0)
		{
			elem.at(0) = val;
			head = tail = 0;
			sz++;
		}
		else if (tail == elem.size() - 1)
		{
			elem.at(0) = val;
			tail = 0;
			sz++;
		}
		else
		{
			elem.at(++tail) = val;
			sz++;
		}
	}

	void resize(int new_size)
	{
		if (tail == sz - 1)
		{
			elem.resize(new_size);
			return;
		}
		std::vector<T>tmp(new_size);
		for (int i = 0; i < sz - head; ++i)
			tmp.at(i) = elem.at(head + i);
		for (int i = 0; i <= tail; ++i)
			tmp.at(sz - head + i) = elem.at(i);
		elem = tmp;
		sz = new_size;
	}

	T pop_font()
	{
		if (sz == 0)
			return -1;
		if (head == tail)
		{
			T& tmp = elem[head];
			sz--;
			if (sz == 0)
				head = tail = 0;
			return tmp;
		}
		else
		{
			T& tmp = elem[head++];
			if (head == elem.size())
				head = 0;
			sz--;
			return tmp;
		}
	}

	T front() const
	{
		return elem.at(head);
	}
};

int main()
{
	int n;
	std::cin >> n;
	cycled_queue<int> a(n);
	bool ans = 1;
	for (int i = 0; i < n; ++i)
	{

		char cmd;
		std::cin >> cmd;
		int val;
		std::cin >> val;
		switch (cmd)
		{
		case '3':
			a.push_back(val);
			break;
		case '2':
			if (val != a.pop_font())
				ans = 0;
			break;
		default:
			std::cout << "impossible";
		}
	}
	ans == 1 ? std::cout << "YES" : std::cout << "NO";
}