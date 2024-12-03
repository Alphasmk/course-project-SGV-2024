#include "stdafx.h"

namespace LT
{
	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE)
		{
			ERROR_THROW(2);
		}
		
		LexTable lextable;
		lextable.size = 0;
		lextable.maxsize = size;
		lextable.table = new Entry[size];

		return lextable;
	}

	void Add(LexTable& lextable, Entry& entry)
	{
		if (lextable.size >= LT_MAXSIZE)
		{
			ERROR_THROW(3);
		}

		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		if (n > lextable.size || n < 0)
		{
			ERROR_THROW(4);
		};
		
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable.maxsize = 0;
		lextable.size = 0;
	}
}