#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>

namespace CG
{
	struct Generator
	{
		LT::LexTable lt;
		IT::IdTable it;
		OT::OpTable ot;
		std::ofstream out;

		Generator(LT::LexTable lt, IT::IdTable it, OT::OpTable _ot);

		void Head();
		void Data();
		void Code();
		void Constants();
	};
}