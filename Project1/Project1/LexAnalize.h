#pragma once
#include "stdafx.h"
#include "FST.h"
#include <vector>
#include <map>
namespace LA
{
	void LexAnalize(In::INTAB&, LT::LexTable&, IT::IdTable&, std::vector<std::pair<std::string, IT::Entry>>&);
	bool isSeparator(char);
	bool checkChain(std::string, FST::FST);
	void printLexTable(LT::LexTable);
	void printIdTable(IT::IdTable);
	void searchScope(int& lb, int& rb, bool& isInScope, const std::vector<std::pair<std::string, int>> words, int&);
};