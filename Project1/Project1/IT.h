﻿#pragma once

#define ID_MAXSIZE 20 // максимальное количество символов в идентификаторе
#define TI_MAXSIZE 4096 // максимальное количество записей в таблице идентификаторов
#define TI_INT_DEFAULT 0x00000000 // значение по умолчанию для типа integer
#define TT_STR_DEFAULT 0x00 // значение по умолчанию для типа string
#define TT_CHAR_DEFAULT 0x00 // значение по умолчанию для типа char
#define TT_BOOL_DEFAULT false // значение по умолчанию для типа bool
#define TI_NULLIDX 0xffffffff // нет элемента в таблицы идентификаторов
#define TI_STR_MAXSIZE 255 
#define MAX_SCOPE 99999;
namespace IT
{
	enum IDDATATYPE // типы данных идентификаторов
	{
		INT = 1,
		STR = 2,
		CHAR = 3,
		BOOL = 4,
		VD = 5
	};

	enum IDTYPE // типы идентификаторов
	{
		V = 1, // переменная
		F = 2, // функция
		P = 3, // параметр
		L = 4 // литерал
	};

	struct Entry // запись в таблице идентификаторов
	{
		int idxfirstLE; // индекс первой строки в таблице лексем
		char id[ID_MAXSIZE]; // идентификатор
		IDDATATYPE iddatatype; // тип данных идентификатора
		IDTYPE idtype; // тип идентификатора
		bool isPointer;
		int PointeridxfirstLE = -1;

		union
		{
			int vint; // значение для типа integer
			char vchar; // значение для типа char
			bool vbool; // значение для типа bool
			struct
			{
				int len; // количество символов в string
				char str[TI_STR_MAXSIZE - 1]; // символы string
			} vstr; // значение для типа string

		} value;
	};

	struct IdTable // экземпляр таблицы идентификаторов
	{
		int maxsize; // максимальное количество записей в таблице идентификаторов < TI_MAXSIZE
		int size; // текущий размер таблицы идентификаторов < maxsize
		Entry* table; // массив строк таблицы идентификаторов
	};

	IdTable Create(int size); // создание таблицы идентификаторов

	void Add( // добавление записи в таблицу идентификаторов
		IdTable& idtable, // таблица идентификаторов
		Entry entry // строка таблицы идентификаторов
	);

	Entry GetEntry( // получение записи из таблицы идентификаторов
		IdTable& idtable, // таблица идентификаторов
		int n // номер записи в таблице идентификаторов
	);

	int IsId( // поиск идентификатора в таблице идентификаторов вернуть индекс или TI_NULLIDX
		IdTable& idtable, // таблица идентификаторов
		char id[ID_MAXSIZE] // идентификатор
	);

	void Delete(IdTable& idtable); // удаление таблицы идентификаторов
}
