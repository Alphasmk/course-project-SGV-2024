#include "stdafx.h"
namespace Error
{
	ERRORS errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),//LA
		ERROR_ENTRY(1, "Системный сбой"),//LA
		ERROR_ENTRY(2, "Невозможно создать таблицу. Слишком большой размер"),//LA
		ERROR_ENTRY(3, "Невозможно добавить элемент. Таблица заполнена"),//LA
		ERROR_ENTRY(4, "Неверный индекс"),//LA
		ERROR_ENTRY(5, "Ошибочное завершение кода программы"),//LA
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"), //LA
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY(103, "Неправильный формат параметра"), //параметры
		ERROR_ENTRY(104, "Превышена длина входного параметра"), //параметры
		ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY(107, "Ошибка при открытии файла"), //параметры
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Не удалось открыть файл с исходным кодом (-in)"), //параметры
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле(-in)"),//LA
		ERROR_ENTRY(112, "Ошибка при создании файла протокола(-log)"),//LA
		ERROR_ENTRY(113, "Ошибка при разборе исходного кода"), //LA
		ERROR_ENTRY(114, "Ошибка при анализе лексемы"),//LA
		ERROR_ENTRY(115, "Необъявленный идентификатор"), //LA
		ERROR_ENTRY(116, "Повторно объявленный идентификатор переменной"), //LA
		ERROR_ENTRY(117, "Повторно объявленный идентификатор функции"), //LA
		ERROR_ENTRY(118, "Использование зарезервивованного идентификатора функции _pow()"), //LA
		ERROR_ENTRY(119, "Использование зарезервивованного идентификатора функции _exp()"), //LA
		ERROR_ENTRY(120, "Использование зарезервивованного идентификатора функции _pause()"), //LA
		ERROR_ENTRY(121, "Слишком большая длина имени идентификатора функции(>5 символов)"), //LA
		ERROR_ENTRY(122, "Использование зарезервированного слова"), //LA
		ERROR_ENTRY(123, "Ошибка при объявлении идентификатора"), //LA
		ERROR_ENTRY(124, "Слишком большая длина имени идентификатора переменной(>8)"), //LA
		ERROR_ENTRY_NODEF(125),
		ERROR_ENTRY_NODEF(126),
		ERROR_ENTRY_NODEF(127),
		ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"),
	  ERROR_ENTRY(601, "Ошибочный оператор"),
	  ERROR_ENTRY(602, "Ошибка в выражении"),
	  ERROR_ENTRY(603, "Ошибка в параметрах функции"),
	  ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции библиотеки"),
	  ERROR_ENTRY(605, "Ошибка в параметрах условного оператора"),//семантика
	  ERROR_ENTRY(606, "Ошибка в параметрах вызываемой функции"),//семантика
	  ERROR_ENTRY(607, "Несоответствие типов при сравнении"),//семантика
	  ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609), ERROR_ENTRY_NODEF(610),
	  ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
	  ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),  ERROR_ENTRY_NODEF10(690),
	  ERROR_ENTRY(700, "Ошибка при обработке оператора польской нотации"),
	  ERROR_ENTRY(701, "Main не объявлен"),//семантика
	  ERROR_ENTRY(702, "Ошибочное кол-во параметров функции _pow()"),//семантика
	  ERROR_ENTRY(703, "Ошибочное кол-во параметров функции _exp()"),//семантика
	  ERROR_ENTRY(704, "Неверный тип данных параметра функции _pow()"),//семантика
	  ERROR_ENTRY(705, "Неверный тип данных параметра функции _exp()"),//семантика
	  ERROR_ENTRY(706, "Функция _pause() должна вызываться без параметров"),//семантика
	  ERROR_ENTRY(707, "Ошибочный тип члена выражения"),//семантика
	  ERROR_ENTRY(708, "Неверный тип данных функции _print"),//семантика
	  ERROR_ENTRY(709, "Ошибочное кол-во параметров функии _print"),//семантика
	  ERROR_ENTRY(710, "Несоответствие типа функции ее возвращаемому значению"),//семантика
	  ERROR_ENTRY_NODEF(711),
	  ERROR_ENTRY_NODEF(712),
	  ERROR_ENTRY_NODEF(713),
	  ERROR_ENTRY_NODEF(714),
	  ERROR_ENTRY_NODEF(715),
	  ERROR_ENTRY_NODEF(716),
	  ERROR_ENTRY_NODEF(717),
	  ERROR_ENTRY_NODEF(718),
	  ERROR_ENTRY_NODEF(719),
	  ERROR_ENTRY_NODEF10(720), ERROR_ENTRY_NODEF10(730),
	  ERROR_ENTRY_NODEF10(740), ERROR_ENTRY_NODEF10(750),
	  ERROR_ENTRY_NODEF10(760), ERROR_ENTRY_NODEF10(770),
	  ERROR_ENTRY_NODEF10(780), ERROR_ENTRY_NODEF10(790),
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
