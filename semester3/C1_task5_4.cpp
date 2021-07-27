/*
Task: Дано выражение в инфиксной записи.
Вычислить его, используя перевод выражения в постфиксную запись.
Выражение не содержит отрицительных чисел. Количество операций ≤ 100.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using std::string;
using std::stack;

int priority(char c)
{
	switch (c)
	{
	case '(':
	case ')':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:	//invalid char
		return -1;
	}
}
bool is_operator(char c)
{
	return c == '+' or c == '*' or c == '/' or c == '-';
}

int str_count(const std::string& left, char oper, const  std::string& right)
{
	int a = std::stoi(left);
	int b = std::stoi(right);
	switch (oper)
	{
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '+':
		return a + b;
	case '-':
		return a - b;
	default:
		return 0;
	}

}

int count_from_postfix(const std::string& postfix)
{
	std::stack<std::string> mstack;
	for (int i = 0; i < postfix.size(); ++i)
	{
		if (isdigit(postfix[i]))
		{
			string tmp;
			tmp += postfix[i];
			while (isdigit(postfix[++i]))
				tmp += postfix[i];
			mstack.push(tmp);
		}
		else if (is_operator(postfix[i]))
		{
			std::string right = mstack.top();
			mstack.pop();
			std::string left = mstack.top();
			mstack.pop();
			int res = str_count(left, postfix[i], right);
			mstack.push(std::to_string(res));
		}
	}
	return  std::stoi(mstack.top());
}

string convert_to_postfix(const string& s)
{
	string stack;
	string res;
	char last_x = '1';
	for (auto x : s)
	{
		if (isdigit(x))
		{
			if (!isdigit(last_x))
				res += ' ';
			res += x;
		}
		else if (stack.empty() or x == '(')
			stack += x;
		else if (is_operator(x))
		{
			while (!stack.empty() and priority(x) <= priority(stack.back()))
			{
				res += ' ';
				res += stack.back();
				stack.pop_back();
			}
			stack += x;
		}
		else if (x == ')')
		{
			while (stack.back() != '(')
			{
				res += ' ';
				res += stack.back();
				stack.pop_back();
			}
			stack.pop_back();
		}
		last_x = x;
	}
	while (!stack.empty())
	{
		res += ' ';
		res += stack.back();
		stack.pop_back();
	}
	return res;
}
int main()
{
	string s;
	std::getline(std::cin, s);
	std::cout << count_from_postfix(convert_to_postfix(s));
	//std::cout << count_expression(convert_to_postfix(s)) << std::endl;
}




