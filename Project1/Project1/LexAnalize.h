#pragma once
#include "stdafx.h"
#include "FST.h"
#include "OT.h"
#include <vector>
#include <map>
namespace LA
{
	void LexAnalize(In::INTAB&, LT::LexTable&, IT::IdTable&, OT::OpTable&, std::vector<std::pair<std::string, IT::Entry>>&);
	bool isSeparator(char);
	bool checkChain(std::string, FST::FST);
	void printLexTable(LT::LexTable);
	void printIdTable(IT::IdTable);
};
