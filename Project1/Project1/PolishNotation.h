#pragma once
#include <stack>
namespace PolishNotation
{
	int checkPriority(char);
	void PolishNotation(int iter, IT::IdTable& it, LT::LexTable& lt);
	bool isSeparator(char symb);
}
