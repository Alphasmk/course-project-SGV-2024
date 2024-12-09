﻿#include "stdafx.h"
using namespace std;

int _tmain(int argc, const _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	Parm::PARM parm;
	Log::LOG log = Log::INITLOG;
	try
	{
		parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::INTAB in = In::getin(parm.in, parm.out);

		vector<pair<string, IT::Entry>> ids;
		LT::LexTable lextable = LT::Create(in.size);
		IT::IdTable idtable = IT::Create(in.size);
		OT::OpTable optable = OT::Create();
		IT::Entry enter;

		LA::LexAnalize(in, lextable, idtable, optable, ids);
		LA::printLexTable(lextable);
		LA::printIdTable(idtable);
		SemAnalize::SemAnalize(lextable, idtable);
		OT::Print(optable);

		MFST_TRACE_START						//отладка
			MFST::Mfst mfst(lextable, GRB::getGreibach());			//автомат
		mfst.start();											// старт синтаксического анализа

		mfst.savededucation();									//сохранить правила вывода

		mfst.printrules();

		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i - 1].lexema == LEX_EQUALS)
			{
				PolishNotation::PolishNotation(i, idtable, lextable, optable);
			}
		}
		LA::printLexTable(lextable);
		Log::Close(log);
		LT::Delete(lextable);
		IT::Delete(idtable);
		OT::Delete(optable);
	}
	catch (Error::ERRORS e)
	{
		cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
		if (e.inext.line)
			Log::WriteError(log, e);
		if (e.id != 100)
		{
			Log::Close(log);
		}
	}
	system("pause");
	return 0;
}
