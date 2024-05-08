#pragma once

#include<string>
#include<iostream>

class RPN
{
public:
	RPN(const char formula[]);
	~RPN();
	int calc(void);

private:
	const std::string _formula;
	RPN();
	RPN(RPN& other);
	RPN& operator=(RPN& rhs);
};