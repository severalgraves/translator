#pragma once

#include <iostream>

using namespace std;

enum type { number, operation, open_bracket, close_bracket };

class Term
{
public:
	type token;

	type GetType()
	{
		return token;
	}
	virtual void print() = 0;
};

class Number : public Term
{
public:
	double value;

	Number(double num)
	{
		token = type::number;

		value = num;
	}

	double getValue()
	{
		return value;
	}

	void print()
	{
		cout << value << " ";
	}
};

class Operator : public Term
{
public:
	char op;

	Operator(char oper)
	{
		token = type::operation;

		op = oper;
	}
	int Priority()
	{
		if (op == '*' || op == '/')
		{
			return 1;
		}

		if (op == '+' || op == '-')
		{
			return 0;
		}

		throw invalid_argument("unidentified operation");
	}

	char getOp() const
	{
		return op;
	}

	void print()
	{
		cout << op << " ";
	}
};

class Bracket : public Term
{
public:
	char value;

	Bracket(char br)
	{
		if (br == '(')
		{
			token = type::open_bracket;
		}

		else
		{
			token = type::close_bracket;
		}

		value = br;
	}
	char get_op() const
	{
		return value;
	}

	void print()
	{
		cout << value << " ";
	}
};
