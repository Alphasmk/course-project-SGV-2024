﻿#pragma once
#include "stdafx.h"
namespace SemAnalize
{
	void SemAnalize(LT::LexTable, IT::IdTable);//
	void SearchMain(LT::LexTable);//
	void CheckLiterals(IT::IdTable&);//
	void CheckOperations(LT::LexTable, IT::IdTable);
	void CheckPow(LT::LexTable, IT::IdTable);//
	void CheckExp(LT::LexTable, IT::IdTable);//
	void CheckPause(LT::LexTable, IT::IdTable);
}