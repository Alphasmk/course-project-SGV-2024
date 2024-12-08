#pragma once
#include "stdafx.h"
namespace OT
{
	enum OTYPE
	{
		A = 1, // +
		M = 2, // *
		D = 3, // /
		S = 4, // -
		IE = 5, // ==
		INE = 6, // !=
		G = 7, // >
		L = 8, // <
		GE = 9, // >=
		LE = 10, // <=
		LB = 11, // (
		RB = 12 // )
	};

	struct Operator
	{
		OTYPE operatorType;
		int idxLE;
	};

	struct OpTable
	{
		int size;
		Operator* table;
	};

	OpTable Create();
	void Add(OpTable& ot, Operator oper);
	Operator GetOperator(OpTable& ot, int n);
	void Delete(OpTable& ot);
	void Print(OpTable ot);
}
