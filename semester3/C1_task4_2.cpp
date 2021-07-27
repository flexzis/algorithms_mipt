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
class cycled_deque
{
	size_t front;
	size_t back;
	size_t q_size;
	std::vector<T> elem;
public:

	cycled_deque() 
	{ 
		cycled_deque(10);
	}

	cycled_deque(size_t n) : q_size{ 0 }
	{
		if (n < 10)
			elem.resize(10);
		else
			elem.resize(n);
		front = 0;
		back = 0;
	}

	cycled_deque(const cycled_deque& other) :
		front{ other.front_ind() }
		, back{ other.back_ind() }
		, q_size{ other.size() }
		, elem{ other.data() }
	{}

	cycled_deque(cycled_deque&& other) :
		front{ other.front_ind() }
		, back{ other.back_ind() }
		, q_size{ other.size() }
		, elem{ other.data() }
	{
		other.front = other.back = other.q_size = 0;
		other.elem.clear();
	}

	cycled_deque& operator =(const cycled_deque& other)
	{
		if (this == &other)
			return *this;
		front = other.front_ind();
		back = other.back_ind();
		size = other.size();
		elem = other.data();
		return *this;
	}

	cycled_deque& operator =(const cycled_deque&& other)
	{
		front = other.front_ind();
		back = other.back_ind();
		size = other.size();
		elem = other.data();
		other.front = other.back = other.q_size = 0;
		other.elem.clear();
		return *this;
	}
	bool isFull() const
	{
		return ((front == 1 && back == elem.size()) ||
			front == back + 1);
	}

	bool isEmpty() const
	{
		return q_size == 0;
	}

	size_t front_ind() const
	{
		return front;
	}
	size_t back_ind() const
	{
		return back;
	}
	size_t size() const
	{
		return q_size;
	}
	const std::vector<T>& data() const
	{
		return elem;
	}
	void push_back(const T& val)
	{
		if (isFull())
			reserve(2 * q_size);
		if (front == 0)
		{
			front = 1;
			back = 1;
		}

		else if (back == elem.size())
			back = 1;
		else
			back++;
		elem[back - 1] = val;
		q_size++;
	}

	void push_front(const T& val)
	{
		if (isFull())
			reserve(2 * q_size);

		if (front == 0)
		{
			front = 1;
			back = 1;
		}
		else if (front == 1)
			front = elem.size();

		else
			front--;

		elem[front - 1] = val;
		q_size++;
	}

	void pop_front()
	{
		if (isEmpty())
			return;
		if (front == back)
		{
			front = 0;
			back = 0;
		}
		else
			if (front == elem.size())
				front = 1;
			else
				front++;
		q_size--;
	}

	T get_front() const
	{
		if (!isEmpty())
			return elem[front - 1];
		else
			return -1;
	}
	T get_back() const
	{
		if (!isEmpty())
			return elem[back - 1];
		else
			return -1;
	}

	void pop_back()
	{
		if (isEmpty())
			reserve(2* q_size);
		if (front == back)
		{
			front = 0;
			back = 0;
		}
		else if (back == 1)
			back = elem.size();
		else
			back--;
		q_size--;
	}

	void print()
	{
		for (size_t i = 0; i < elem.size(); ++i)
		{
			if (i == back - 1 or i == front - 1)
				std::cout << elem[i];
			else
				std::cout << "_";
		}
		std::cout << "     " << q_size << std::endl;
	}

	void reserve(size_t new_size)
	{
		//works only if deque is full!!!
		if (new_size < elem.size())
			return;
		std::vector<T> tmp(new_size);
		if (front < back)
		{
			std::copy(elem.begin(), elem.begin() + front, tmp.begin());
			std::copy(elem.begin() + front, elem.end(), tmp.end() - (elem.size() - back + 1));
			back = tmp.size() - (elem.size() - back);
		}
		else
		{
			std::copy(elem.begin(), elem.begin() + back, tmp.begin());
			std::copy(elem.begin() + back, elem.end(), tmp.end() - (elem.size() - front + 1));
			front = tmp.size() - (elem.size() - front);
		}
		elem = tmp;
	}
};

int main()
{
	size_t n;
	std::cin >> n;
	bool ans = 1;
	cycled_deque<int> a(n);
	for (int i = 0; i < n; ++i)
	{
		char cmd;
		std::cin >> cmd;
		int val;
		std::cin >> val;
		switch (cmd)
		{
		case '1':
			a.push_front(val);
			break;
		case '2':
			if (val != a.get_front())
				ans = 0;
			a.pop_front();
			break;
		case '3':
			a.push_back(val);
			break;
		case '4':
			if (val != a.get_back())
				ans = 0;
			a.pop_back();
			break;
		default:
			std::cout << "impossible";
		}
	}
	ans == 1 ? std::cout << "YES" : std::cout << "NO";
}




