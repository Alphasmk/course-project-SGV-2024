#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
		{
			ERROR_THROW(2);
		}

		IdTable idtable;
		idtable.maxsize = size;
		idtable.size = 0;
		idtable.table = new Entry[size];

		return idtable;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size > TI_MAXSIZE)
		{
			ERROR_THROW(3);
		}

		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n > idtable.size || n < 0)
		{
			ERROR_THROW(4);
		}
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].id == id)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable.size = 0;
		idtable.maxsize = 0;
	}
}