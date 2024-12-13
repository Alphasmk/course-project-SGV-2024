﻿#pragma once
#include "GRB.h"
#include"Error.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	//  Грамматика (Грейбах) 
	Greibach greibach(NS('S'), TS('$'),				//стартовый символ, дно стека
		6,											//количество правил
		Rule(NS('S'), GRB_ERROR_SERIES + 0,			
			5,		//S →	m{NrE;};|tfi(F){NrE;};S|m{NrE;};S|tfi(F){NrE;};|i{NrE;}
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(7, TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			//Rule::Chain(8, TS('i'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,			//Операторы программы
			16,		//N	→dti;| rE;| i = E; | dtfi(F);|dti;N|rE;N|i=E;N|dtfi(F);N|pE;|pE;N
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			//Rule::Chain(5, TS('i'), TS('c'), TS('i'), TS(';'), NS('N')),
			/*Rule::Chain(3, TS('r'), NS('E'), TS(';')),*/
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('i'), NS('E'), TS(';')),
			Rule::Chain(3, NS('E'), TS(';'), NS('N')),
			//Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			//Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(10, TS('s'), TS('('), TS('i'), TS('c'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(11, TS('s'), TS('('), TS('i'), TS('c'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')),
			Rule::Chain(15, TS('s'), TS('('), TS('i'), TS('c'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')),
			Rule::Chain(14, TS('s'), TS('('), TS('i'), TS('c'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), TS(';'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2,			//Выражение
			9,		//E →i|l|(E)|i(W)|iM|lM|(E)M|i(W)M|
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(3, TS('i'), TS('('), TS(')'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 3,			//Подвыражение
			4,		//W	→i|l|i,W|l,W
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4,			//Параметры функции
			2,		//F	→ti|ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 2,			//Выражение
			2,		//M →vE|vEM
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		)
	);
}
