#include "RPN.hpp"
#include<stack>
#include<cctype>

RPN::~RPN(void){}

RPN::RPN(const char formula[]): _formula(formula)
{
}

static long long doOp(char op, long long a, long long b)
{
	if (op == '+')
		return (a + b);
	else if (op == '-')
		return (a - b);
	else if (op == '*')
		return (a * b);
	else if (op == '/' and b != 0 )
		return (a / b);
	else
		throw std::exception();
	return (0);
}

int RPN::calc(void)
{
	std::stack<long long int> s;

	for(std::string::const_iterator it = _formula.begin(); it != _formula.end(); ++it)
	{
		if (isdigit(*it))
			s.push(long(*it - '0'));
		else if (*it == '+' or *it == '-' or *it == '*' or *it == '/')
		{
			if (s.size() < 2)
				throw std::runtime_error("stack too small");
			long long a = s.top(); s.pop();
			long long b = s.top(); s.pop();
			s.push(doOp(*it, b, a));
		}
		else if(*it == '\0')
			break ;
		else
			throw std::runtime_error("not a digit or operator");

		// ensure there is a space after every token
		++it;
		if (it == _formula.end())
			break;
		if(*it != ' ')
		{
			throw std::runtime_error("not a space");
		}
	}
	
	if (s.size() == 1)
		return (s.top());
	else
		throw std::runtime_error("stack not of size 1");
}