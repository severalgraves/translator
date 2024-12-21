#pragma once

#include <iostream>
#include "stack_queue.h"
#include "term.h"
#include <string>
#include <vector>

using namespace std;

class Translator
{
private:

	string str;
	vector<Term*> polish;
	vector<Term*> str_terms;

	
public:

	Translator(string s) : str(s) {}

	~Translator()
	{
		for (size_t i = 0; i < str_terms.size(); i++)
		{
			delete str_terms[i];
		}
	}
	double solve()
	{
		if (!LexicalAnalysis())
		{
			throw "lexical analysis error";
		}

		if (!SyntacticAnalysis())
		{
			throw "syntactic analysis error";
		}

		ToPostfix();

		for (size_t i = 0; i < str.size(); i++)
		{
			cout << str[i];
		}

		cout << "\n";

		for (size_t i = 0; i < str_terms.size(); i++)
		{
			str_terms[i]->print();
		}
		cout << "\n";

		for (size_t i = 0; i < polish.size(); i++)
		{
			polish[i]->print();
		}
		cout << "\n";

		double d = Calculation();

		cout << d << "\n";

		return d;
	}

	bool LexicalAnalysis()
	{
		size_t i = 0;

		while (i < str.size())
		{
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				str_terms.push_back(new Operator(str[i]));
				i++;
			}
			else if (str[i] >= '0' && str[i] <= '9')
			{
				string::size_type sz;
				str_terms.push_back(new Number(stod(str.substr(i), &sz)));
				i += sz;
			}
			else if (str[i] == '(' || str[i] == ')')
			{
				str_terms.push_back(new Bracket(str[i]));
				i++;
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	void ToPostfix()
	{
		Stack<Term*> stack;

		for (size_t i = 0; i < str_terms.size(); i++)
		{
			switch (str_terms[i]->GetType())
			{
			case type::number:
			{
				polish.push_back(str_terms[i]);
				break;
			}

			case type::open_bracket:
			{
				stack.push(str_terms[i]);
				break;
			}

			case type::close_bracket:
			{
				while (stack.top()->GetType() != type::open_bracket)
				{
					polish.push_back(stack.top());

					stack.pop();
				}
				stack.pop();
				break;
			}

			case type::operation:
			{
				while (!stack.isEmpty() && stack.top()->GetType() == type::operation && ((Operator*)(stack.top()))->Priority() >= ((Operator*)(str_terms[i]))->Priority())
				{
					polish.push_back(stack.top());
					stack.pop();
				}
				stack.push(str_terms[i]);
			}
			break;
			}
		}
		while (!stack.isEmpty())
		{
			polish.push_back(stack.top());
			stack.pop();
		}
	}

	int Conformity(char s)
	{
		if (s == '(')
		{
			return ')';
		}
	}

	bool SyntacticAnalysis()
	{
		Stack<char> stack;
		bool lastWasOperator = true;

		for (size_t i = 0; i < str_terms.size(); i++)
		{
			Term* currentTerm = str_terms[i];

			switch (currentTerm->GetType())
			{
			case type::open_bracket:
				if (!lastWasOperator && !stack.isEmpty()) return false;
				stack.push(((Bracket*)currentTerm)->get_op());
				lastWasOperator = true;
				break;

			case type::close_bracket:
				if (lastWasOperator) return false;
				if (!stack.isEmpty() && ((Bracket*)currentTerm)->get_op() == Conformity(stack.top())) {
					stack.pop();
				}
				else {
					return false; 
				}
				lastWasOperator = false; 
				break;

			case type::operation:

				if (lastWasOperator) return false;
				lastWasOperator = true; 
				break;

			case type::number:
				if (!lastWasOperator && !stack.isEmpty()) return false;
				lastWasOperator = false; 
				break;

			default:
				return false; 
			}
		}

		return stack.isEmpty() && !lastWasOperator;
	}

	double Calculation() {

		Stack<double> stack_num;

		for (size_t i = 0; i < polish.size(); i++)
		{
			switch (polish[i]->GetType())
			{
			case type::number:
			{
				stack_num.push(((Number*)(polish[i]))->value);
				break;
			}

			case type::operation:
			{
				double operand_1 = stack_num.top();
				stack_num.pop();

				double operand_2 = stack_num.top();
				stack_num.pop();

				switch (((Operator*)(polish[i]))->op)
				{

				case '+':
				{
					stack_num.push(operand_2 + operand_1);
					break;
				}
				case '-':
				{
					stack_num.push(operand_2 - operand_1);
					break;
				}
				case '*':
				{
					stack_num.push(operand_2 * operand_1);
					break;
				}
				case '/':
				{
					if (operand_1 == 0.0)
					{
						throw "division by zero";
					}
					else stack_num.push(operand_2 / operand_1);

					break;
				}
				}
				break;
			}
			}
		}
		return stack_num.top();
	}

};

