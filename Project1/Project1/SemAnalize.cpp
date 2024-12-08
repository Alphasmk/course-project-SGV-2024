#include "stdafx.h"
#include "SemAnalize.h"
#include "Error.h"
namespace SemAnalize
{
	FST::FST typePow("", 5,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('o', 3)),
		FST::NODE(1, FST::RELATION('w', 4)),
		FST::NODE());

	FST::FST typeExp("", 5,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('e', 2)),
		FST::NODE(1, FST::RELATION('x', 3)),
		FST::NODE(1, FST::RELATION('p', 4)),
		FST::NODE());

	FST::FST typePause("", 7,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('a', 3)),
		FST::NODE(1, FST::RELATION('u', 4)),
		FST::NODE(1, FST::RELATION('s', 5)),
		FST::NODE(1, FST::RELATION('e', 6)),
		FST::NODE());

	void SearchMain(LT::LexTable lt)
	{
		bool isFound = false;
		for (int i = 0; i < lt.size; i++)
		{
			if (lt.table[i].lexema == LEX_MAIN)
			{
				isFound = true;
				break;
			}
		}

		if (!isFound)
		{
			ERROR_THROW(701);
		}
	}

	void CheckLiterals(IT::IdTable& it)
	{
		for (int i = 0; i < it.size; i++)
		{
			if (it.table[i].idtype == IT::L)
			{
				if (it.table[i].iddatatype == IT::INT)
				{
					if (it.table[i].value.vint > 255)
					{
						it.table[i].value.vint = 255;
					}
					else if (it.table[i].value.vint < 0)
					{
						it.table[i].value.vint = 0;
					}
				}
				else if (it.table[i].iddatatype == IT::STR)
				{
					if (it.table[i].value.vstr.len > 11)
					{
						it.table[i].value.vstr.str[11] = '\0';
						it.table[i].value.vstr.len = 11;
					}
				}
			}
		}
	}

	void CheckPow(LT::LexTable lt, IT::IdTable it)
	{
		int paramCounter = 0;
		for (int i = 0; i < it.size; i++)
		{
			if (LA::checkChain(it.table[i].id, typePow))
			{
				int iter, sn = -1, il = -1;
				bool isOk = true;
				for (int k = 0; k < lt.size; k++)
				{
					if (lt.table[k].idxTI == i + 1)
					{
						iter = k + 1;
						sn = lt.table[k].sn;
						il = k;
						break;
					}
				}
				for (iter; lt.table[iter].lexema != ')'; iter++)
				{
					if (lt.table[iter].lexema != ',' && lt.table[iter].lexema != '(')
					{
						if (it.table[lt.table[iter].idxTI - 1].iddatatype != IT::INT)
						{
							isOk = false;
						}
						paramCounter++;
					}
				}
				if (paramCounter != 2)
				{
					ERROR_THROW_IN(702, sn, il);
				}
				if (!isOk)
				{
					ERROR_THROW_IN(704, sn, il);
				}
				paramCounter = 0;
			}
		}
	}

	void CheckExp(LT::LexTable lt, IT::IdTable it)
	{
		int paramCounter = 0;
		for (int i = 0; i < it.size; i++)
		{
			if (LA::checkChain(it.table[i].id, typeExp))
			{
				int iter, sn = -1, il = -1;
				bool isOk = true;
				for (int k = 0; k < lt.size; k++)
				{
					if (lt.table[k].idxTI == i + 1)
					{
						iter = k + 1;
						sn = lt.table[k].sn;
						il = k;
						break;
					}
				}
				for (iter; lt.table[iter].lexema != ')'; iter++)
				{
					if (lt.table[iter].lexema != ',' && lt.table[iter].lexema != '(')
					{
						if (it.table[lt.table[iter].idxTI - 1].iddatatype != IT::INT)
						{
							isOk = false;
						}
						paramCounter++;
					}
				}
				if (paramCounter != 2)
				{
					ERROR_THROW_IN(703, sn, il);
				}
				if (!isOk)
				{
					ERROR_THROW_IN(705, sn, il);
				}
				paramCounter = 0;
			}
		}
	}

	void CheckPause(LT::LexTable lt, IT::IdTable it)
	{
		int paramCounter = 0;
		for (int i = 0; i < it.size; i++)
		{
			if (LA::checkChain(it.table[i].id, typePause))
			{
				int iter, sn, il;
				bool isOk = true;
				for (int k = 0; k < lt.size; k++)
				{
					if (lt.table[k].idxTI == i + 1)
					{
						iter = k + 1;
						sn = lt.table[k].sn;
						il = k;
						break;
					}
				}
				for (iter; lt.table[iter].lexema != ')'; iter++)
				{
					if (lt.table[iter].lexema != ',' && lt.table[iter].lexema != '(')
					{
						paramCounter++;
					}
				}
				if (paramCounter > 0)
				{
					ERROR_THROW_IN(706, sn, il);
				}
				paramCounter = 0;
			}
		}
	}

	void SemAnalize(LT::LexTable lt, IT::IdTable it)
	{
		SearchMain(lt);
		CheckLiterals(it);
		CheckPow(lt, it);
		CheckExp(lt, it);
		CheckPause(lt, it);
	}
}
