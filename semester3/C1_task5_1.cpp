/*
Task: Дан фрагмент последовательности скобок, состоящей из символов (){}[].
Требуется определить, возможно ли продолжить фрагмент в обе стороны, получив корректную последовательность.
Длина исходной последовательности ≤ 800000.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using std::string;
using std::stack;
char match_bracket(char c)
{
	switch (c)
	{
	case '{':
		return '}';
	case '[':
		return ']';
	case '(':
		return ')';
	case '}':
		return '{';
	case ']':
		return '[';
	case ')':
		return '(';
	default:
		return 'e';
	}
}
string bracket_sequence(const string& s)
{
	if (s.empty())
		return "IMPOSSIBLE";
	string res;
	stack<char> for_right;
	stack<char> for_left;

	for (auto x : s)
	{
		switch (x)
		{
		case'(':
		case'{':
		case '[':
			for_right.push(x);
		break;
		default:
			if (for_right.empty())
			{
				for_left.push(x);
			}
			else if (x == match_bracket(for_right.top()))
				for_right.pop();
			else
				return "IMPOSSIBLE";
		}
	}
	while (!for_left.empty())
	{
		res.push_back(match_bracket(for_left.top()));
		for_left.pop();
	}
	for (auto x : s)
		res.push_back(x);
	while (!for_right.empty())
	{
		res.push_back(match_bracket(for_right.top()));
		for_right.pop();
	}
	return res;
}
int main()
{
	string s;
	std::getline(std::cin, s);
	std::cout << bracket_sequence(s);
}