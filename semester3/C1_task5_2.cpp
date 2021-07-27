/*
Task: Пара слов называется стековой анаграмой, если одно слово можно получить из другого,
проведя последовательность стековых операций с его буквами
(взять очередную букву исходного слова и поместить ее в стек; взять букву из стека и добавить ее в конец выходного слова).
Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций,
переводящую первое слово во второе. Все буквы в слове различные. Длина анаграммы ≤ 10000.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using std::string;
using std::stack;
string is_stack_anagram(const string& s1, const string& s2)
{
	stack<char> stack;
	int j = 0;
	for (int i = 0; i < s1.size(); ++i)
	{
	//	std::cout << s1[i] << " " << s2[j] << std::endl;
		if (s1[i] == s2[j])
			++j;
		else
		{
			if (stack.empty())
				stack.push(s1[i]);
			else
			{
				char c = stack.top();
				stack.pop();
				if (s2[j] == c)
				{
					++j;
					--i;
				}
				else
				{
					stack.push(c);
					stack.push(s1[i]);
				}
			}
		}
	}
	while (!stack.empty())
	{
		//std::cout << s2[j] << "    ";
		//char c = stack.top();
		//std::cout << c << "\n";
		if (s2[j] != stack.top())
		{
			return "NO";
		}
		else
			++j;
		stack.pop();
	}

	return "YES";
}

int main()
{
	string s1, s2;
	char c;
	while (c = std::cin.get())
	{
		if (c == ' ')
			break;
		else
			s1.push_back(c);
	}
	std::cin >> s2;
	std::cout << is_stack_anagram(s1, s2);
}



