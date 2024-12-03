#include "stdafx.h"

Log::LOG Log::getlog(wchar_t logfile[])
{
	LOG log;
	std::ofstream* file = new std::ofstream(logfile);
	if (!file->is_open())
	{
		delete file;
		ERROR_THROW(112);
	}
	wcscpy_s(log.logfile, logfile);
	log.stream = file;
	return log;
}

void Log::WriteLine(LOG log, const char* c, ...)
{
	if (!log.stream->is_open())
	{
		ERROR_THROW(112);
	}

	va_list args;
	va_start(args, c);

	const char* str = c; 
	if (str != NULL) 
	{
		(*log.stream) << str;
	}

	while (true)
	{
		str = va_arg(args, const char*);
		if (str == "")
		{
			break;
		}
		(*log.stream) << str;
	}
	(*log.stream) << std::endl;

	va_end(args);
}

void Log::WriteLine(LOG log, wchar_t* c, ...)
{
	if (!log.stream->is_open())
	{
		ERROR_THROW(112);
	}

	va_list args;
	va_start(args, c);

	char buf[256];

	wchar_t* str;
	while ((str = va_arg(args, wchar_t*)) != L"")
	{
		wcstombs(buf, str, sizeof(buf));
		buf[sizeof(buf) - 1] = '\0';
		(*log.stream) << buf;
	}
	(*log.stream) << std::endl;

	va_end(args);
}

void Log::WriteLog(LOG log)
{
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);

	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);

	(*log.stream) << "---Протокол--- " << buffer << " ---" << std::endl;
}


void Log::WriteParm(LOG log, Parm::PARM parm)
{
	char buf[80];
	wcstombs(buf, parm.in, sizeof(buf));
	(*log.stream) << "in: " << buf << std::endl;
	wcstombs(buf, parm.out, sizeof(buf));
	(*log.stream) << "out: " << buf << std::endl;
	wcstombs(buf, parm.log, sizeof(buf));
	(*log.stream) << "log: " << buf << std::endl;
}

void Log::WriteIn(LOG log, In::INTAB in)
{
	(*log.stream) << "Количество символов: " << in.size << std::endl
		<< "Проигнорировано: " << in.ignor << std::endl
		<< "Количество строк: " << in.lines << std::endl;
}

void Log::WriteError(LOG log, Error::ERRORS error)
{
	if (error.id == 100)
	{
		std::ofstream* inerr = new std::ofstream("log.txt");
		(*inerr) << "Ошибка " << error.id << ": " << error.message;
		if (error.inext.col >= 0 && error.inext.line >= 0)
		{
			(*inerr) << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		}
		inerr->close();
		delete inerr;
		return;
	}
	if (log.stream->is_open())
	{
		(*log.stream) << "Ошибка ";
		(*log.stream) << error.id;
		(*log.stream) << ": ";
		(*log.stream) << error.message;
	}
	if (error.inext.col >=0 && error.inext.line >= 0)
	{
		(*log.stream) << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
	}
}

void Log::Close(LOG log)
{
	if (log.stream->is_open())
	{
		log.stream->close();
		delete log.stream;
	}
}