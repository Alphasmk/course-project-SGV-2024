#include "stdafx.h"
namespace Error
{
	ERRORS errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY(2, "Невозможно создать таблицу. Слишком большой размер"),
		ERROR_ENTRY(3, "Невозможно добавить элемент. Таблица заполнена"),
		ERROR_ENTRY(4, "Неверный индекс"),
		ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY(103, "Неправильный формат параметра"),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Не удалось открыть файл с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле(-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY(113, "Ошибка при разборе исходного кода"),
		ERROR_ENTRY(114, "Ошибка при анализе лексемы"),
		ERROR_ENTRY(115, "Необъявленный идентификатор"),
		ERROR_ENTRY(116, "Повторно объявленный идентификатор переменной"),
		ERROR_ENTRY(117, "Повторно объявленный идентификатор функции"),
		ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"),
	  ERROR_ENTRY(601, "Ошибочный оператор"),
	  ERROR_ENTRY(602, "Ошибка в выражении"),
	  ERROR_ENTRY(603, "Ошибка в параметрах функции"),
	  ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
	  ERROR_ENTRY(605, "Ошибка в параметрах условного оператора"),
	  ERROR_ENTRY_NODEF10(700), ERROR_ENTRY_NODEF10(800), ERROR_ENTRY_NODEF10(900)
	};

	ERRORS geterror(int id)
	{
		for (int i = 0; i < ERROR_MAX_ENTRY; i++)
		{
			if (errors[i].id == id)
				return errors[i];
		}
		return errors[0];
	}

	ERRORS geterrorin(int id, int line, int col)
	{
		ERRORS err = geterror(id);
		err.inext.line = line;
		err.inext.col = col;
		return err;
	}
}
