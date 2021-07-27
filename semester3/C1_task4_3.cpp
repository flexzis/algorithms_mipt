/*
Task: В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 2 - pop front
a = 3 - push back
Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
*/
#include <iostream>
#include <vector>
#include <exception>
template<class T> 
class my_stack
{
	std::vector<int> elem;
public:
	my_stack() { }
	void push_back(const T& val)
	{
		elem.push_back(val);
	}
	void pop_back()
	{
		elem.pop_back();
	}
	T get_back() const
	{
		return elem.back();
	}

	size_t size()
	{
		return elem.size();
	}
};
template<class T>
class my_queue
{
	my_stack<T> data1;
	my_stack<T> data2;
public:
	my_queue() { }
	void push_back(const T& val)
	{
		data1.push_back(val);
	}
	void pop_front()
	{
		if (data2.size())
			data2.pop_back();
		else if (data1.size())
		{
			while (data1.size())
			{
				data2.push_back(data1.get_back());
				data1.pop_back();
			}
			data2.pop_back();
		}
		return;
	}
	T get_front() 
	{
		if (data2.size())
			return data2.get_back();
		else if (data1.size())
		{
			while (data1.size())
			{
				data2.push_back(data1.get_back());
				data1.pop_back();
			}
			return data2.get_back();
		}
	return -1;
	}
	void size()
	{
		return data1.size() + data2.size();
	}
};
int main()
{
	size_t n;
	std::cin >> n;
	bool ans = 1;
	my_queue<int> a;
	for (int i = 0; i < n; ++i)
	{
		char cmd;
		std::cin >> cmd;
		int val;
		std::cin >> val;
		switch (cmd)
		{
		case '2':
			if (val != a.get_front())
				ans = 0;
			a.pop_front();
			break;
		case '3':
			a.push_back(val);
			break;
		default:
			std::cout << "impossible";
		}
	//		a.reserve(2 * a.data().size());
	//	std::cout << "b = " << a.back << "  f = " << a.front << std::endl;
	//		a.print();
	}
	ans == 1 ? std::cout << "YES" : std::cout << "NO";
}




