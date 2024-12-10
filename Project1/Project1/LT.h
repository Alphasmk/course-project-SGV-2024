#pragma once

#define LEXEMA_FIXSIZE 1   // фиксированный размер лексемы
#define LT_MAXSIZE  4096 // максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX 0xffffffff // нет элемента таблицы индентификаторов

#define LEX_INTEGER 't' // лексема для integer
#define LEX_STRING 't' // лексема для string
#define LEX_CHAR 't' // лексема для char
#define LEX_BOOL 't' // лексема для bool
#define LEX_ID 'i' // лексема для идентификатора
#define LEX_LITERAL 'l' // лексема для литерала
#define LEX_BOOLLITERAL 'l' // лексема для bool литерала
#define LEX_FUNCTION 'f' // лексема для функции
#define LEX_DECLARE 'd' // лексема для declare
#define LEX_RETURN 'r' // лексема для return
#define LEX_SEMICOLON ';' // лексема для ;
#define LEX_COMMA ',' // лексема для ,
#define LEX_LEFTBRACE '{' // лексема для {
#define LEX_RIGHTBRACE '}' // лексема для }
#define LEX_LEFTHESIS '(' // лексема для (
#define LEX_RIGHTHESIS ')' // лексема для )
#define LEX_RIGHTSQUARE ']' // лексема для ]
#define LEX_LEFTSQUARE '[' // лексема для [
#define LEX_PLUS 'v' // лексема для +
#define LEX_MINUS 'v' // лексема для -
#define LEX_STAR 'v' // лексема для *
#define LEX_DIRSLASH 'v' // лексема для /
#define LEX_MAIN 'm' // лексема для main
#define LEX_EQUALS '=' // лексема для =
#define LEX_ISEQUALS 'c' // лексема для ==
#define LEX_ISNOTEQUALS 'c' // лексема для ==
#define LEX_GREATEROREQUAL 'c' // лексема для >=
#define LEX_LESSOREQUAL 'c' // лексема для <=
#define LEX_GREATER 'c' // лексема для >
#define LEX_LESS 'c' // лексема для <
#define LEX_IF 's' // лексема для if
#define LEX_ELSE 'e' // лексема для else
#define LEX_POW 'i' // лексема для pow
#define LEX_EXP 'i' // лексема для exp
#define LEX_PAUSE 'i' // лексема для pause
#define LEX_PRINT 'i' // лексема для print

namespace LT // таблица лексем
{
	struct Entry
	{
		char lexema; // лексема
		int sn; // номер строки
		int idxTI; // индекс в таблице идентификаторов
		int idxOP = -1; // индекс в таблице операторов
	};

	struct LexTable
	{
		int maxsize; // максимальный размер таблицы
		int size; // текущий размер таблицы
		Entry* table; // таблица лексем
	};

	LexTable Create( // создание таблицы лексем
		int size // максимальный размер таблицы
	);

	void Add( // добавление лексемы в таблицу
		LexTable& lextable, // таблица лексем
		Entry& entry // лексема
	);

	Entry GetEntry( // получение лексемы из таблицы
		LexTable& lextable, // таблица лексем
		int n // номер лексемы
	);

	void Delete( // удаление таблицы лексем
		LexTable& lextable // таблица лексем
	);

}
