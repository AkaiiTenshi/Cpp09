#include "RPN.hpp"
#include <iostream>

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
	(void)other;
}

RPN& RPN::operator=(const RPN& other)
{
	(void)other;
	return *this;
}

RPN::~RPN()
{
}

bool RPN::isNumber(const std::string& token) const
{
	if (token.length() != 1)
		return false;
	return (token[0] >= '0' && token[0] <= '9');
}

bool RPN::isOperator(const std::string& token) const
{
	if (token.length() != 1)
		return false;
	return (token[0] == '+' || token[0] == '-' || 
			token[0] == '*' || token[0] == '/');
}

int RPN::calculus_func(int a, int b, char op) const
{
	switch (op)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: division by zero");
			return a / b;
		default:
			throw std::runtime_error("Error: invalid operator");
	}
}

int RPN::launch_rpn(const std::string& expression) const
{
	std::stack<int> operands;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (isNumber(token))
		{
			operands.push(token[0] - '0');
		}
		else if (isOperator(token))
		{
			if (operands.size() < 2)
				throw std::runtime_error("Error: not enough operands");
			
			int right = operands.top();
			operands.pop();
			int left = operands.top();
			operands.pop();
			
			int result = calculus_func(left, right, token[0]);
			operands.push(result);
		}
		else
		{
			throw std::runtime_error("Error: invalid token");
		}
	}

	if (operands.size() != 1)
		throw std::runtime_error("Error: invalid expression");
	
	return operands.top();
}
