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

	FST::FST typeFunction("", 9,
		FST::NODE(1, FST::RELATION('f', 1)),
		FST::NODE(1, FST::RELATION('u', 2)),
		FST::NODE(1, FST::RELATION('n', 3)),
		FST::NODE(1, FST::RELATION('c', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),
		FST::NODE(1, FST::RELATION('i', 6)),
		FST::NODE(1, FST::RELATION('o', 7)),
		FST::NODE(1, FST::RELATION('n', 8)),
		FST::NODE()
	);

	FST::FST typePrintInt("", 10,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE(1, FST::RELATION('i', 4)),
		FST::NODE(1, FST::RELATION('n', 5)),
		FST::NODE(1, FST::RELATION('t', 6)),
		FST::NODE(1, FST::RELATION('I', 7)),
		FST::NODE(1, FST::RELATION('n', 8)),
		FST::NODE(1, FST::RELATION('t', 9)),
		FST::NODE()
	);

	FST::FST typePrintStr("", 10,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE(1, FST::RELATION('i', 4)),
		FST::NODE(1, FST::RELATION('n', 5)),
		FST::NODE(1, FST::RELATION('t', 6)),
		FST::NODE(1, FST::RELATION('S', 7)),
		FST::NODE(1, FST::RELATION('t', 8)),
		FST::NODE(1, FST::RELATION('r', 9)),
		FST::NODE()
	);

	FST::FST typePrintBool("", 11,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE(1, FST::RELATION('i', 4)),
		FST::NODE(1, FST::RELATION('n', 5)),
		FST::NODE(1, FST::RELATION('t', 6)),
		FST::NODE(1, FST::RELATION('B', 7)),
		FST::NODE(1, FST::RELATION('o', 8)),
		FST::NODE(1, FST::RELATION('o', 9)),
		FST::NODE(1, FST::RELATION('l', 10)),
		FST::NODE()
	);


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
			if (LA::checkChain(it.table[i].id, typeExp) && !LA::checkChain(it.table[i].id, typeFunction))
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
			if (LA::checkChain(it.table[i].id, typePause) && !LA::checkChain(it.table[i].id, typeFunction))
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

	void CheckPrint(LT::LexTable lt, IT::IdTable it)
	{
		int paramCounter = 0;
		for (int i = 0; i < it.size; i++)
		{
			if ((LA::checkChain(it.table[i].id, typePrintInt) || LA::checkChain(it.table[i].id, typePrintStr) || LA::checkChain(it.table[i].id, typePrintBool)) && !LA::checkChain(it.table[i].id, typeFunction))
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
						if (LA::checkChain(it.table[i].id, typePrintInt) && it.table[lt.table[iter].idxTI - 1].iddatatype != IT::INT)
						{
							isOk = false;
						}
						else if (LA::checkChain(it.table[i].id, typePrintStr) && (it.table[lt.table[iter].idxTI - 1].iddatatype != IT::STR && it.table[lt.table[iter].idxTI - 1].iddatatype != IT::CHAR))
						{
							isOk = false;
						}
						else if (LA::checkChain(it.table[i].id, typePrintBool) && it.table[lt.table[iter].idxTI - 1].iddatatype != IT::BOOL)
						{
							isOk = false;
						}
						paramCounter++;
					}
				}
				if (paramCounter != 1)
				{
					ERROR_THROW_IN(709, sn, il);
				}
				if (!isOk)
				{
					ERROR_THROW_IN(708, sn, il);
				}
				paramCounter = 0;
			}
		}
	}

	void CheckOperations(LT::LexTable lt, IT::IdTable it)
	{
		IT::IDDATATYPE type;
		vector<pair<string, vector<IT::IDDATATYPE>>> params;
		int sn = -1, il = -1, i = 0;
		for (i; i < lt.size; i++)
		{
			sn = lt.table[i].sn;
			il = i;
			if (it.table[lt.table[i].idxTI - 1].idtype == IT::F && lt.table[i - 1].lexema == 'f')
			{
				int k = i + 1;
				pair<string, vector<IT::IDDATATYPE>> exParams;
				exParams.first.assign(it.table[lt.table[i].idxTI - 1].id);
				while (lt.table[k].lexema != ')')
				{
					if (it.table[lt.table[k].idxTI - 1].idtype == IT::P)
					{
						exParams.second.push_back(it.table[lt.table[k].idxTI - 1].iddatatype);
					}
					k++;
				}
				params.push_back(exParams);
			}
			else if (lt.table[i].lexema == '=')
			{
				type = it.table[lt.table[i - 1].idxTI].iddatatype;
				int k = i + 1;
				while (lt.table[k].lexema != ';')
				{
					switch (lt.table[k].lexema)
					{
					case 'i':
						if (it.table[lt.table[k].idxTI - 1].iddatatype == type && it.table[lt.table[k].idxTI - 1].idtype == IT::F && strcmp(it.table[lt.table[k].idxTI - 1].id, "_exp") != 0 && strcmp(it.table[lt.table[k].idxTI - 1].id, "_pow") != 0 && strcmp(it.table[lt.table[k].idxTI - 1].id, "_pause") != 0)
						{
							string buf;
							int paramCounter = 0, funId = 0;
							buf = it.table[lt.table[k].idxTI - 1].id;
							k = k + 1;
							while (true)
							{
								if (lt.table[k].lexema == 'i' || lt.table[k].lexema == 'l')
								{
									for (int j = 0; j < params.size(); j++)
									{
										if (params[j].first == buf)
										{
											funId = j;
											if (params[j].second[paramCounter] == it.table[lt.table[k].idxTI - 1].iddatatype)
											{
												paramCounter++;
											}
											else
											{
												ERROR_THROW_IN(606, sn, il);
											}
										}
										break;
									}
								}
								else if (lt.table[k].lexema != ',' && lt.table[k].lexema != '(' && paramCounter != params[funId].second.size())
								{
									ERROR_THROW_IN(606, sn, il);
								}
								else if (lt.table[k].lexema == ')')
								{
									break;
								}
								k++;
							}
						}
						else if (it.table[lt.table[k].idxTI - 1].iddatatype != type)
						{
							ERROR_THROW_IN(707, sn, il)
						}
						break;
					case 'l':
						if (it.table[lt.table[k].idxTI - 1].iddatatype != type)
						{
							ERROR_THROW_IN(707, sn, il);
						}
						break;
					}
					k++;
					i = k;
				}
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
		CheckPrint(lt, it);
		CheckOperations(lt, it);
	}
}
