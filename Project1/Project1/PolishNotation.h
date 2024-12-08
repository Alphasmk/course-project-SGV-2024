#pragma once
#include <stack>
namespace PolishNotation
{
	int checkPriority(char, LT::Entry entry, OT::OpTable&);
	void PolishNotation(int iter, IT::IdTable& it, LT::LexTable& lt, OT::OpTable& op);
	bool isSeparator(char symb);
}
