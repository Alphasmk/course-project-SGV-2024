#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

namespace Log
{
	struct LOG {
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const LOG INITLOG{ L"log.txt", NULL };
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, const char* c, ...);
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::INTAB in);
	void WriteError(LOG log, Error::ERRORS error);
	void Close(LOG log);
}
