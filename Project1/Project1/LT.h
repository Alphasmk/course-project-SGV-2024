#pragma once

#define LEXEMA_FIXSIZE 1   // ������������� ������ �������
#define LT_MAXSIZE  4096 // ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff // ��� �������� ������� ����������������

#define LEX_INTEGER 't' // ������� ��� integer
#define LEX_STRING 't' // ������� ��� string
#define LEX_CHAR 't' // ������� ��� char
#define LEX_BOOL 't' // ������� ��� bool
#define LEX_ID 'i' // ������� ��� ��������������
#define LEX_LITERAL 'l' // ������� ��� ��������
#define LEX_BOOLLITERAL 'l' // ������� ��� bool ��������
#define LEX_FUNCTION 'f' // ������� ��� �������
#define LEX_DECLARE 'd' // ������� ��� declare
#define LEX_RETURN 'r' // ������� ��� return
#define LEX_PRINT 'p' // ������� ��� print
#define LEX_SEMICOLON ';' // ������� ��� ;
#define LEX_COMMA ',' // ������� ��� ,
#define LEX_LEFTBRACE '{' // ������� ��� {
#define LEX_RIGHTBRACE '}' // ������� ��� }
#define LEX_LEFTHESIS '(' // ������� ��� (
#define LEX_RIGHTHESIS ')' // ������� ��� )
#define LEX_RIGHTSQUARE ']' // ������� ��� ]
#define LEX_LEFTSQUARE '[' // ������� ��� [
#define LEX_PLUS 'v' // ������� ��� +
#define LEX_MINUS 'v' // ������� ��� -
#define LEX_STAR 'v' // ������� ��� *
#define LEX_DIRSLASH 'v' // ������� ��� /
#define LEX_MAIN 'm' // ������� ��� main
#define LEX_EQUALS '=' // ������� ��� =
#define LEX_ISEQUALS 'c' // ������� ��� ==
#define LEX_ISNOTEQUALS 'c' // ������� ��� ==
#define LEX_GREATEROREQUAL 'c' // ������� ��� >=
#define LEX_LESSOREQUAL 'c' // ������� ��� <=
#define LEX_GREATER 'c' // ������� ��� >
#define LEX_LESS 'c' // ������� ��� <
#define LEX_IF 's' // ������� ��� if
#define LEX_ELSE 'e' // ������� ��� else
#define LEX_POW 'i' // ������� ��� pow
#define LEX_EXP 'i' // ������� ��� exp
#define LEX_PAUSE 'i' // ������� ��� pause

namespace LT // ������� ������
{
	struct Entry
	{
		char lexema; // �������
		int sn; // ����� ������
		int idxTI; // ������ � ������� ���������������
	};

	struct LexTable
	{
		int maxsize; // ������������ ������ �������
		int size; // ������� ������ �������
		Entry* table; // ������� ������
	};

	LexTable Create( // �������� ������� ������
		int size // ������������ ������ �������
	);

	void Add( // ���������� ������� � �������
		LexTable& lextable, // ������� ������
		Entry& entry // �������
	);

	Entry GetEntry( // ��������� ������� �� �������
		LexTable& lextable, // ������� ������
		int n // ����� �������
	);

	void Delete( // �������� ������� ������
		LexTable& lextable // ������� ������
	);

}