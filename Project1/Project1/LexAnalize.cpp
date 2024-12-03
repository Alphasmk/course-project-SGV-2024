#include "stdafx.h"
#include "LexAnalize.h"
#include "FST.h"
#include <iomanip>
#include <utility>
#include <unordered_set>
#include <stack>
#include <map>

struct PairHash {
	size_t operator()(const std::pair<std::string, int>& p) const {
		// Хэшируем строку и целое число, комбинируем их
		return std::hash<std::string>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};

struct PairEqual {
	bool operator()(const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) const {
		// Сравниваем оба элемента пары
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
};

namespace LA
{
	FST::FST typeInteger("", 8,
		FST::NODE(1, FST::RELATION('i', 1)),
		FST::NODE(1, FST::RELATION('n', 2)),
		FST::NODE(1, FST::RELATION('t', 3)),
		FST::NODE(1, FST::RELATION('e', 4)),
		FST::NODE(1, FST::RELATION('g', 5)),
		FST::NODE(1, FST::RELATION('e', 6)),
		FST::NODE(1, FST::RELATION('r', 7)),
		FST::NODE()
	);

	FST::FST typeString("", 7,
		FST::NODE(1, FST::RELATION('s', 1)),
		FST::NODE(1, FST::RELATION('t', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE(1, FST::RELATION('i', 4)),
		FST::NODE(1, FST::RELATION('n', 5)),
		FST::NODE(1, FST::RELATION('g', 6)),
		FST::NODE()
	);

	FST::FST typeBool("", 5,
		FST::NODE(1, FST::RELATION('b', 1)),
		FST::NODE(1, FST::RELATION('o', 2)),
		FST::NODE(1, FST::RELATION('o', 3)),
		FST::NODE(1, FST::RELATION('l', 4)),
		FST::NODE()
	);

	FST::FST typeChar("", 5,
		FST::NODE(1, FST::RELATION('c', 1)),
		FST::NODE(1, FST::RELATION('h', 2)),
		FST::NODE(1, FST::RELATION('a', 3)),
		FST::NODE(1, FST::RELATION('r', 4)),
		FST::NODE()
	);

	FST::FST typeFunction("", 9,
		FST::NODE(1, FST::RELATION('f', 1)),
		FST::NODE(1, FST::RELATION('u', 2)),
		FST::NODE(1, FST::RELATION('n', 3)),
		FST::NODE(1, FST::RELATION('c', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),
		FST::NODE(1, FST::RELATION('i', 6)),
		FST::NODE(1, FST::RELATION('o', 7)),
		FST::NODE(1, FST::RELATION('n', 8)),
		FST::NODE()
	);

	FST::FST typeDeclare("", 8,
		FST::NODE(1, FST::RELATION('d', 1)),
		FST::NODE(1, FST::RELATION('e', 2)),
		FST::NODE(1, FST::RELATION('c', 3)),
		FST::NODE(1, FST::RELATION('l', 4)),
		FST::NODE(1, FST::RELATION('a', 5)),
		FST::NODE(1, FST::RELATION('r', 6)),
		FST::NODE(1, FST::RELATION('e', 7)),
		FST::NODE()
	);

	FST::FST typeReturn("", 7,
		FST::NODE(1, FST::RELATION('r', 1)),
		FST::NODE(1, FST::RELATION('e', 2)),
		FST::NODE(1, FST::RELATION('t', 3)),
		FST::NODE(1, FST::RELATION('u', 4)),
		FST::NODE(1, FST::RELATION('r', 5)),
		FST::NODE(1, FST::RELATION('n', 6)),
		FST::NODE()
	);

	FST::FST typeMain("", 5,
		FST::NODE(1, FST::RELATION('m', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),
		FST::NODE()
	);

	FST::FST typePrint("", 6,
		FST::NODE(1, FST::RELATION('p', 1)),
		FST::NODE(1, FST::RELATION('r', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),
		FST::NODE()
	);

	FST::FST typeSpace("", 2,
		FST::NODE(1, FST::RELATION(' ', 1)),
		FST::NODE()
	);
	FST::FST typeLeftBrace("", 2,
		FST::NODE(1, FST::RELATION('{', 1)),
		FST::NODE()
	);
	FST::FST typeRightBrace("", 2,
		FST::NODE(1, FST::RELATION('}', 1)),
		FST::NODE()
	);
	FST::FST typeLeftThesis("", 2,
		FST::NODE(1, FST::RELATION('(', 1)),
		FST::NODE()
	);
	FST::FST typeRightThesis("", 2,
		FST::NODE(1, FST::RELATION(')', 1)),
		FST::NODE()
	);
	FST::FST typeLeftSquare("", 2,
		FST::NODE(1, FST::RELATION('[', 1)),
		FST::NODE()
	);
	FST::FST typeRightSquare("", 2,
		FST::NODE(1, FST::RELATION(']', 1)),
		FST::NODE()
	);
	FST::FST typeSemicolon("", 2,
		FST::NODE(1, FST::RELATION(';', 1)),
		FST::NODE()
	);
	FST::FST typeComma("", 2,
		FST::NODE(1, FST::RELATION(',', 1)),
		FST::NODE()
	);
	FST::FST typePlus("", 2,
		FST::NODE(1, FST::RELATION('+', 1)),
		FST::NODE());
	FST::FST typeMinus("", 2,
		FST::NODE(1, FST::RELATION('-', 1)),
		FST::NODE());
	FST::FST typeDel("", 2,
		FST::NODE(1, FST::RELATION('/', 1)),
		FST::NODE());
	FST::FST typeMulti("", 2,
		FST::NODE(1, FST::RELATION('*', 1)),
		FST::NODE());
	FST::FST typeEquals("", 2,
		FST::NODE(1, FST::RELATION('=', 1)),
		FST::NODE());

	FST::FST typeIsEquals("", 3,
		FST::NODE(1, FST::RELATION('=', 1)),
		FST::NODE(1, FST::RELATION('=', 2)),
		FST::NODE());

	FST::FST typeIsNotEquals("", 3,
		FST::NODE(1, FST::RELATION('!', 1)),
		FST::NODE(1, FST::RELATION('=', 2)),
		FST::NODE());

	FST::FST typeGreaterOrEquals("", 3,
		FST::NODE(1, FST::RELATION('>', 1)),
		FST::NODE(1, FST::RELATION('=', 2)),
		FST::NODE());

	FST::FST typePow("", 5,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('o', 3)),
		FST::NODE(1, FST::RELATION('w', 4)),
		FST::NODE());

	FST::FST typeExp("", 5,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('e', 2)),
		FST::NODE(1, FST::RELATION('x', 3)),
		FST::NODE(1, FST::RELATION('p', 4)),
		FST::NODE());

	FST::FST typePause("", 7,
		FST::NODE(1, FST::RELATION('_', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('a', 3)),
		FST::NODE(1, FST::RELATION('u', 4)),
		FST::NODE(1, FST::RELATION('s', 5)),
		FST::NODE(1, FST::RELATION('e', 6)),
		FST::NODE());

	FST::FST typeLessOrEquals("", 3,
		FST::NODE(1, FST::RELATION('<', 1)),
		FST::NODE(1, FST::RELATION('=', 2)),
		FST::NODE());

	FST::FST typeIf("", 3,
		FST::NODE(1, FST::RELATION('i', 1)),
		FST::NODE(1, FST::RELATION('f', 2)),
		FST::NODE());

	FST::FST typeElse("", 5,
		FST::NODE(1, FST::RELATION('e', 1)),
		FST::NODE(1, FST::RELATION('l', 2)),
		FST::NODE(1, FST::RELATION('s', 3)),
		FST::NODE(1, FST::RELATION('e', 4)),
		FST::NODE());

	FST::FST typeTrue("", 5,
		FST::NODE(1, FST::RELATION('t', 1)),
		FST::NODE(1, FST::RELATION('r', 2)),
		FST::NODE(1, FST::RELATION('u', 3)),
		FST::NODE(1, FST::RELATION('e', 4)),
		FST::NODE());

	FST::FST typeFalse("", 6,
		FST::NODE(1, FST::RELATION('f', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('l', 3)),
		FST::NODE(1, FST::RELATION('s', 4)),
		FST::NODE(1, FST::RELATION('e', 5)),
		FST::NODE());

	FST::FST typeLess("", 2,
		FST::NODE(1, FST::RELATION('<', 1)),
		FST::NODE());

	FST::FST typeGreater("", 2,
		FST::NODE(1, FST::RELATION('>', 1)),
		FST::NODE());

	FST::FST typeSlashN("", 2,
		FST::NODE(1, FST::RELATION('\n', 1)),
		FST::NODE());

	FST::FST typeIdentificator("", 2,
		FST::NODE(52,
			FST::RELATION('a', 0), FST::RELATION('b', 0),
			FST::RELATION('c', 0), FST::RELATION('d', 0),
			FST::RELATION('e', 0), FST::RELATION('f', 0),
			FST::RELATION('g', 0), FST::RELATION('h', 0),
			FST::RELATION('i', 0), FST::RELATION('j', 0),
			FST::RELATION('k', 0), FST::RELATION('l', 0),
			FST::RELATION('m', 0), FST::RELATION('n', 0),
			FST::RELATION('o', 0), FST::RELATION('p', 0),
			FST::RELATION('q', 0), FST::RELATION('r', 0),
			FST::RELATION('s', 0), FST::RELATION('t', 0),
			FST::RELATION('u', 0), FST::RELATION('v', 0),
			FST::RELATION('w', 0), FST::RELATION('x', 0),
			FST::RELATION('y', 0), FST::RELATION('z', 0),
			FST::RELATION('a', 1), FST::RELATION('b', 1),
			FST::RELATION('c', 1), FST::RELATION('d', 1),
			FST::RELATION('e', 1), FST::RELATION('f', 1),
			FST::RELATION('g', 1), FST::RELATION('h', 1),
			FST::RELATION('i', 1), FST::RELATION('j', 1),
			FST::RELATION('k', 1), FST::RELATION('l', 1),
			FST::RELATION('m', 1), FST::RELATION('n', 1),
			FST::RELATION('o', 1), FST::RELATION('p', 1),
			FST::RELATION('q', 1), FST::RELATION('r', 1),
			FST::RELATION('s', 1), FST::RELATION('t', 1),
			FST::RELATION('u', 1), FST::RELATION('v', 1),
			FST::RELATION('w', 1), FST::RELATION('x', 1),
			FST::RELATION('y', 1), FST::RELATION('z', 1)
		),

		FST::NODE()
	);

	FST::FST typeCharLiteral("", 4,

		FST::NODE(1,
			FST::RELATION('\'', 1)),
		FST::NODE(192,
			FST::RELATION('!', 2), FST::RELATION('@', 2), FST::RELATION('#', 2), FST::RELATION('$', 2), FST::RELATION('%', 2), FST::RELATION('^', 2),
			FST::RELATION('&', 2), FST::RELATION('*', 2), FST::RELATION('(', 2), FST::RELATION(')', 2), FST::RELATION('-', 2), FST::RELATION('_', 2),
			FST::RELATION('+', 2), FST::RELATION('=', 2), FST::RELATION('~', 2), FST::RELATION('`', 2), FST::RELATION('1', 2), FST::RELATION('2', 2),
			FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2),
			FST::RELATION('9', 2), FST::RELATION('0', 2), FST::RELATION('	', 2), FST::RELATION(' ', 2), FST::RELATION('q', 2), FST::RELATION('w', 2),
			FST::RELATION('e', 2), FST::RELATION('r', 2), FST::RELATION('t', 2), FST::RELATION('y', 2), FST::RELATION('u', 2), FST::RELATION('i', 2),
			FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('{', 2), FST::RELATION('[', 2), FST::RELATION('}', 2), FST::RELATION(']', 2),
			FST::RELATION('\\', 2), FST::RELATION('|', 2), FST::RELATION('Q', 2), FST::RELATION('W', 2), FST::RELATION('R', 2), FST::RELATION('T', 2), FST::RELATION('Y', 2),
			FST::RELATION('U', 2), FST::RELATION('I', 2), FST::RELATION('O', 2), FST::RELATION('P', 2), FST::RELATION('a', 2), FST::RELATION('s', 2),
			FST::RELATION('d', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('j', 2), FST::RELATION('k', 2),
			FST::RELATION('l', 2), FST::RELATION(':', 2), FST::RELATION(';', 2), FST::RELATION('\'', 2), FST::RELATION('"', 2), FST::RELATION('A', 2),
			FST::RELATION('S', 2), FST::RELATION('D', 2), FST::RELATION('F', 2), FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('J', 2),
			FST::RELATION('K', 2), FST::RELATION('L', 2), FST::RELATION('z', 2), FST::RELATION('x', 2), FST::RELATION('c', 2), FST::RELATION('v', 2),
			FST::RELATION('b', 2), FST::RELATION('n', 2), FST::RELATION('m', 2), FST::RELATION(',', 2), FST::RELATION('.', 2), FST::RELATION('/', 2),
			FST::RELATION('Z', 2), FST::RELATION('X', 2), FST::RELATION('C', 2), FST::RELATION('V', 2), FST::RELATION('B', 2), FST::RELATION('N', 2),
			FST::RELATION('M', 2), FST::RELATION('<', 2), FST::RELATION('>', 2), FST::RELATION('?', 2), FST::RELATION('ё', 2), FST::RELATION('Ё', 2),
			FST::RELATION('й', 2), FST::RELATION('ц', 2), FST::RELATION('у', 2), FST::RELATION('к', 2), FST::RELATION('е', 2), FST::RELATION('н', 2),
			FST::RELATION('г', 2), FST::RELATION('ш', 2), FST::RELATION('щ', 2), FST::RELATION('з', 2), FST::RELATION('х', 2), FST::RELATION('ъ', 2),
			FST::RELATION('Й', 2), FST::RELATION('Ц', 2), FST::RELATION('У', 2), FST::RELATION('К', 2), FST::RELATION('Е', 2), FST::RELATION('Н', 2),
			FST::RELATION('Г', 2), FST::RELATION('Ш', 2), FST::RELATION('Щ', 2), FST::RELATION('З', 2), FST::RELATION('Х', 2), FST::RELATION('Ъ', 2),
			FST::RELATION('ф', 2), FST::RELATION('ы', 2), FST::RELATION('в', 2), FST::RELATION('а', 2), FST::RELATION('п', 2), FST::RELATION('р', 2),
			FST::RELATION('о', 2), FST::RELATION('л', 2), FST::RELATION('д', 2), FST::RELATION('ж', 2), FST::RELATION('э', 2), FST::RELATION('Ф', 2),
			FST::RELATION('Ы', 2), FST::RELATION('В', 2), FST::RELATION('А', 2), FST::RELATION('П', 2), FST::RELATION('Р', 2), FST::RELATION('О', 2),
			FST::RELATION('Л', 2), FST::RELATION('Д', 2), FST::RELATION('Ж', 2), FST::RELATION('Э', 2), FST::RELATION('я', 2), FST::RELATION('ч', 2),
			FST::RELATION('с', 2), FST::RELATION('м', 2), FST::RELATION('и', 2), FST::RELATION('т', 2), FST::RELATION('ь', 2), FST::RELATION('б', 2),
			FST::RELATION('ю', 2), FST::RELATION('Я', 2), FST::RELATION('Ч', 2), FST::RELATION('С', 2), FST::RELATION('М', 2), FST::RELATION('И', 2),
			FST::RELATION('Т', 2), FST::RELATION('Ь', 2), FST::RELATION('Б', 2), FST::RELATION('Ю', 2)
		),
		FST::NODE(1,
			FST::RELATION('\'', 3)),
		FST::NODE()
	);

	FST::FST typeStringLiteral("", 4,

		FST::NODE(1,
			FST::RELATION('\'', 1)),
		FST::NODE(384,
			FST::RELATION('!', 2), FST::RELATION('@', 2), FST::RELATION('#', 2), FST::RELATION('$', 2), FST::RELATION('%', 2), FST::RELATION('^', 2),
			FST::RELATION('&', 2), FST::RELATION('*', 2), FST::RELATION('(', 2), FST::RELATION(')', 2), FST::RELATION('-', 2), FST::RELATION('_', 2),
			FST::RELATION('+', 2), FST::RELATION('=', 2), FST::RELATION('~', 2), FST::RELATION('`', 2), FST::RELATION('1', 2), FST::RELATION('2', 2),
			FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2),
			FST::RELATION('9', 2), FST::RELATION('0', 2), FST::RELATION('	', 2), FST::RELATION(' ', 2), FST::RELATION('q', 2), FST::RELATION('w', 2),
			FST::RELATION('e', 2), FST::RELATION('r', 2), FST::RELATION('t', 2), FST::RELATION('y', 2), FST::RELATION('u', 2), FST::RELATION('i', 2),
			FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('{', 2), FST::RELATION('[', 2), FST::RELATION('}', 2), FST::RELATION(']', 2),
			FST::RELATION('\\', 2), FST::RELATION('|', 2), FST::RELATION('Q', 2), FST::RELATION('W', 2), FST::RELATION('R', 2), FST::RELATION('T', 2), FST::RELATION('Y', 2),
			FST::RELATION('U', 2), FST::RELATION('I', 2), FST::RELATION('O', 2), FST::RELATION('P', 2), FST::RELATION('a', 2), FST::RELATION('s', 2),
			FST::RELATION('d', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('j', 2), FST::RELATION('k', 2),
			FST::RELATION('l', 2), FST::RELATION(':', 2), FST::RELATION(';', 2), FST::RELATION('\'', 2), FST::RELATION('"', 2), FST::RELATION('A', 2),
			FST::RELATION('S', 2), FST::RELATION('D', 2), FST::RELATION('F', 2), FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('J', 2),
			FST::RELATION('K', 2), FST::RELATION('L', 2), FST::RELATION('z', 2), FST::RELATION('x', 2), FST::RELATION('c', 2), FST::RELATION('v', 2),
			FST::RELATION('b', 2), FST::RELATION('n', 2), FST::RELATION('m', 2), FST::RELATION(',', 2), FST::RELATION('.', 2), FST::RELATION('/', 2),
			FST::RELATION('Z', 2), FST::RELATION('X', 2), FST::RELATION('C', 2), FST::RELATION('V', 2), FST::RELATION('B', 2), FST::RELATION('N', 2),
			FST::RELATION('M', 2), FST::RELATION('<', 2), FST::RELATION('>', 2), FST::RELATION('?', 2), FST::RELATION('ё', 2), FST::RELATION('Ё', 2),
			FST::RELATION('й', 2), FST::RELATION('ц', 2), FST::RELATION('у', 2), FST::RELATION('к', 2), FST::RELATION('е', 2), FST::RELATION('н', 2),
			FST::RELATION('г', 2), FST::RELATION('ш', 2), FST::RELATION('щ', 2), FST::RELATION('з', 2), FST::RELATION('х', 2), FST::RELATION('ъ', 2),
			FST::RELATION('Й', 2), FST::RELATION('Ц', 2), FST::RELATION('У', 2), FST::RELATION('К', 2), FST::RELATION('Е', 2), FST::RELATION('Н', 2),
			FST::RELATION('Г', 2), FST::RELATION('Ш', 2), FST::RELATION('Щ', 2), FST::RELATION('З', 2), FST::RELATION('Х', 2), FST::RELATION('Ъ', 2),
			FST::RELATION('ф', 2), FST::RELATION('ы', 2), FST::RELATION('в', 2), FST::RELATION('а', 2), FST::RELATION('п', 2), FST::RELATION('р', 2),
			FST::RELATION('о', 2), FST::RELATION('л', 2), FST::RELATION('д', 2), FST::RELATION('ж', 2), FST::RELATION('э', 2), FST::RELATION('Ф', 2),
			FST::RELATION('Ы', 2), FST::RELATION('В', 2), FST::RELATION('А', 2), FST::RELATION('П', 2), FST::RELATION('Р', 2), FST::RELATION('О', 2),
			FST::RELATION('Л', 2), FST::RELATION('Д', 2), FST::RELATION('Ж', 2), FST::RELATION('Э', 2), FST::RELATION('я', 2), FST::RELATION('ч', 2),
			FST::RELATION('с', 2), FST::RELATION('м', 2), FST::RELATION('и', 2), FST::RELATION('т', 2), FST::RELATION('ь', 2), FST::RELATION('б', 2),
			FST::RELATION('ю', 2), FST::RELATION('Я', 2), FST::RELATION('Ч', 2), FST::RELATION('С', 2), FST::RELATION('М', 2), FST::RELATION('И', 2),
			FST::RELATION('Т', 2), FST::RELATION('Ь', 2), FST::RELATION('Б', 2), FST::RELATION('Ю', 2),
			FST::RELATION('!', 1), FST::RELATION('@', 1), FST::RELATION('#', 1), FST::RELATION('$', 1), FST::RELATION('%', 1), FST::RELATION('^', 1),
			FST::RELATION('&', 1), FST::RELATION('*', 1), FST::RELATION('(', 1), FST::RELATION(')', 1), FST::RELATION('-', 1), FST::RELATION('_', 1),
			FST::RELATION('+', 1), FST::RELATION('=', 1), FST::RELATION('~', 1), FST::RELATION('`', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
			FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1),
			FST::RELATION('9', 1), FST::RELATION('0', 1), FST::RELATION('	', 1), FST::RELATION(' ', 1), FST::RELATION('q', 1), FST::RELATION('w', 1),
			FST::RELATION('e', 1), FST::RELATION('r', 1), FST::RELATION('t', 1), FST::RELATION('y', 1), FST::RELATION('u', 1), FST::RELATION('i', 1),
			FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('{', 1), FST::RELATION('[', 1), FST::RELATION('}', 1), FST::RELATION(']', 1),
			FST::RELATION('\\', 1), FST::RELATION('|', 1), FST::RELATION('Q', 1), FST::RELATION('W', 1), FST::RELATION('R', 1), FST::RELATION('T', 1), FST::RELATION('Y', 1),
			FST::RELATION('U', 1), FST::RELATION('I', 1), FST::RELATION('O', 1), FST::RELATION('P', 1), FST::RELATION('a', 1), FST::RELATION('s', 1),
			FST::RELATION('d', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('j', 1), FST::RELATION('k', 1),
			FST::RELATION('l', 1), FST::RELATION(':', 1), FST::RELATION(';', 1), FST::RELATION('\'', 1), FST::RELATION('"', 1), FST::RELATION('A', 1),
			FST::RELATION('S', 1), FST::RELATION('D', 1), FST::RELATION('F', 1), FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('J', 1),
			FST::RELATION('K', 1), FST::RELATION('L', 1), FST::RELATION('z', 1), FST::RELATION('x', 1), FST::RELATION('c', 1), FST::RELATION('v', 1),
			FST::RELATION('b', 1), FST::RELATION('n', 1), FST::RELATION('m', 1), FST::RELATION(',', 1), FST::RELATION('.', 1), FST::RELATION('/', 1),
			FST::RELATION('Z', 1), FST::RELATION('X', 1), FST::RELATION('C', 1), FST::RELATION('V', 1), FST::RELATION('B', 1), FST::RELATION('N', 1),
			FST::RELATION('M', 1), FST::RELATION('<', 1), FST::RELATION('>', 1), FST::RELATION('?', 1), FST::RELATION('ё', 1), FST::RELATION('Ё', 1),
			FST::RELATION('й', 1), FST::RELATION('ц', 1), FST::RELATION('у', 1), FST::RELATION('к', 1), FST::RELATION('е', 1), FST::RELATION('н', 1),
			FST::RELATION('г', 1), FST::RELATION('ш', 1), FST::RELATION('щ', 1), FST::RELATION('з', 1), FST::RELATION('х', 1), FST::RELATION('ъ', 1),
			FST::RELATION('Й', 1), FST::RELATION('Ц', 1), FST::RELATION('У', 1), FST::RELATION('К', 1), FST::RELATION('Е', 1), FST::RELATION('Н', 1),
			FST::RELATION('Г', 1), FST::RELATION('Ш', 1), FST::RELATION('Щ', 1), FST::RELATION('З', 1), FST::RELATION('Х', 1), FST::RELATION('Ъ', 1),
			FST::RELATION('ф', 1), FST::RELATION('ы', 1), FST::RELATION('в', 1), FST::RELATION('а', 1), FST::RELATION('п', 1), FST::RELATION('р', 1),
			FST::RELATION('о', 1), FST::RELATION('л', 1), FST::RELATION('д', 1), FST::RELATION('ж', 1), FST::RELATION('э', 1), FST::RELATION('Ф', 1),
			FST::RELATION('Ы', 1), FST::RELATION('В', 1), FST::RELATION('А', 1), FST::RELATION('П', 1), FST::RELATION('Р', 1), FST::RELATION('О', 1),
			FST::RELATION('Л', 1), FST::RELATION('Д', 1), FST::RELATION('Ж', 1), FST::RELATION('Э', 1), FST::RELATION('я', 1), FST::RELATION('ч', 1),
			FST::RELATION('с', 1), FST::RELATION('м', 1), FST::RELATION('и', 1), FST::RELATION('т', 1), FST::RELATION('ь', 1), FST::RELATION('б', 1),
			FST::RELATION('ю', 1), FST::RELATION('Я', 1), FST::RELATION('Ч', 1), FST::RELATION('С', 1), FST::RELATION('М', 1), FST::RELATION('И', 1),
			FST::RELATION('Т', 1), FST::RELATION('Ь', 1), FST::RELATION('Б', 1), FST::RELATION('Ю', 1)
		),
		FST::NODE(1,
			FST::RELATION('\'', 3)),
		FST::NODE()
	);

	FST::FST typeNumbLiteral("", 2,
		FST::NODE(20,
			FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0),
			FST::RELATION('5', 0), FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0),
			FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),
			FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1)),
		FST::NODE()

	);

	void LexAnalize(In::INTAB& in, LT::LexTable& lt, IT::IdTable& it, std::vector<std::pair<std::string, IT::Entry>>& ids)
	{
		std::string text = "";

		for (int i = 0; i < strlen((char*)in.text); i++)
		{
			text.push_back(in.text[i]);
		}

		std::vector<std::pair<std::string, int>> words;
		std::string word = "";

		int lineCounter = 1;

		bool isStrLit = false;

		for (int i = 0; i < in.size; i++)
		{
			if (!isStrLit)
			{
				if (((char)in.text[i] == '!' && (char)in.text[i + 1] == '=') || ((char)in.text[i] == '=' && (char)in.text[i + 1] == '=') || ((char)in.text[i] == '<' && (char)in.text[i + 1] == '=') || ((char)in.text[i] == '>' && (char)in.text[i + 1] == '='))
				{
					word.push_back((char)in.text[i]);
				}
				else if (!isSeparator((char)in.text[i]))
				{
					word.push_back((char)in.text[i]);
				}
				else
				{
					if (word != "" && word != "'")
					{
						if (((char)in.text[i] == '=' && (char)in.text[i - 1] == '<') || ((char)in.text[i] == '=' && (char)in.text[i - 1] == '>') || ((char)in.text[i] == '=' && (char)in.text[i - 1] == '=') || ((char)in.text[i] == '=' && (char)in.text[i - 1] == '!'))
						{
							word.push_back((char)in.text[i]);
							i++;
						}
						words.push_back({ word, lineCounter });
						word = "";
					}
					if ((char)in.text[i] != ' ' && (char)in.text[i] != '\t' && (char)in.text[i] != '|' && (char)in.text[i] != '\'')
					{
						if ((char)in.text[i] == '\n')
						{
							word.push_back((char)in.text[i]);
							words.push_back({ word, lineCounter - 1 });
							word = "";
						}
						else
						{
							word.push_back((char)in.text[i]);
							words.push_back({ word, lineCounter });
							word = "";
						}
					}
					if ((char)in.text[i] == '\'')
					{
						word.push_back((char)in.text[i]);
						isStrLit = true;
					}
					if ((char)in.text[i] == '|')
					{
						lineCounter++;
					}
				}
			}
			else
			{
				if ((char)in.text[i] == '\'')
				{
					word.push_back((char)in.text[i]);
					words.push_back({ word, lineCounter });
					word = "";
					isStrLit = false;
				}
				else
				{
					word.push_back((char)in.text[i]);
				}
			}
		}

		if (words.size() == 0)
		{
			ERROR_THROW(113);
		}
		int i = 0;
		stack<string> functionPrefix;
		map<string, int> foundIds;
		short litCounter = 1;
		while (i < words.size())
		{
			if (checkChain(words[i].first, typePlus))
			{
				LT::Entry entry = { LEX_PLUS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeMinus))
			{
				LT::Entry entry = { LEX_MINUS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeInteger))
			{
				LT::Entry entry = { LEX_INTEGER, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeIf))
			{
				LT::Entry entry = { LEX_IF, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeElse))
			{
				LT::Entry entry = { LEX_ELSE, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeString))
			{
				LT::Entry entry = { LEX_STRING, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeChar))
			{
				LT::Entry entry = { LEX_CHAR, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeBool))
			{
				LT::Entry entry = { LEX_BOOL, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeIsEquals))
			{
				LT::Entry entry = { LEX_ISEQUALS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeIsNotEquals))
			{
				LT::Entry entry = { LEX_ISNOTEQUALS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeLessOrEquals))
			{
				LT::Entry entry = { LEX_LESSOREQUAL, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeGreaterOrEquals))
			{
				LT::Entry entry = { LEX_GREATEROREQUAL, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeGreater))
			{
				LT::Entry entry = { LEX_GREATER, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeLess))
			{
				LT::Entry entry = { LEX_LESS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeFunction))
			{
				LT::Entry entry = { LEX_FUNCTION, words[i].second };
				LT::Add(lt, entry);
				functionPrefix.push(words[i + 1].first);
			}
			else if (checkChain(words[i].first, typeDeclare))
			{
				LT::Entry entry = { LEX_DECLARE, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeReturn))
			{
				LT::Entry entry = { LEX_RETURN, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeMain))
			{
				LT::Entry entry = { LEX_MAIN, words[i].second };
				LT::Add(lt, entry);
				functionPrefix.push(words[i].first);
			}
			else if (checkChain(words[i].first, typePrint))
			{
				LT::Entry entry = { LEX_PRINT, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeLeftBrace))
			{
				LT::Entry entry = { LEX_LEFTBRACE, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typePow))
			{
				LT::Entry entry = { LEX_POW, words[i].second };
				LT::Add(lt, entry);
				IT::Entry identry;
				strcpy(identry.id, words[i].first.c_str());
				identry.iddatatype = IT::INT;
				identry.idtype = IT::F;
				identry.idxfirstLE = i;
				ids.push_back({ words[i].first, identry });
			}
			else if (checkChain(words[i].first, typeExp))
			{
				LT::Entry entry = { LEX_EXP, words[i].second };
				LT::Add(lt, entry);
				IT::Entry identry;
				strcpy(identry.id, words[i].first.c_str());
				identry.iddatatype = IT::INT;
				identry.idtype = IT::F;
				identry.idxfirstLE = i;
				ids.push_back({ words[i].first, identry });
			}
			else if (checkChain(words[i].first, typePause))
			{
				LT::Entry entry = { LEX_PAUSE, words[i].second };
				LT::Add(lt, entry);
				IT::Entry identry;
				strcpy(identry.id, words[i].first.c_str());
				identry.iddatatype = IT::VD;
				identry.idtype = IT::F;
				identry.idxfirstLE = i;
				ids.push_back({ words[i].first, identry });
			}
			else if (checkChain(words[i].first, typeRightBrace))
			{
				LT::Entry entry = { LEX_RIGHTBRACE, words[i].second };
				LT::Add(lt, entry);
				functionPrefix.pop();
			}
			else if (checkChain(words[i].first, typeLeftSquare))
			{
				LT::Entry entry = { LEX_LEFTSQUARE, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeRightSquare))
			{
				LT::Entry entry = { LEX_RIGHTSQUARE, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeLeftThesis))
			{
				LT::Entry entry = { LEX_LEFTHESIS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeRightThesis))
			{
				LT::Entry entry = { LEX_RIGHTHESIS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeSemicolon))
			{
				LT::Entry entry = { LEX_SEMICOLON, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeComma))
			{
				LT::Entry entry = { LEX_COMMA, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeDel))
			{
				LT::Entry entry = { LEX_DIRSLASH, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeMulti))
			{
				LT::Entry entry = { LEX_STAR, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeEquals))
			{
				LT::Entry entry = { LEX_EQUALS, words[i].second };
				LT::Add(lt, entry);
			}
			else if (checkChain(words[i].first, typeTrue) || checkChain(words[i].first, typeFalse))
			{
				LT::Entry entry = { LEX_BOOLLITERAL, words[i].second };
				LT::Add(lt, entry);
				IT::Entry identry;
				bool isPointer = false;
				strcpy(identry.id, ("L" + to_string(litCounter)).c_str());
				identry.idxfirstLE = i;
				identry.idtype = IT::L;
				identry.iddatatype = IT::BOOL;
				if (checkChain(words[i].first, typeTrue))
				{
					identry.value.vbool = true;
				}
				else if (checkChain(words[i].first, typeFalse))
				{
					identry.value.vbool = false;
				}
				ids.push_back({ "L" + to_string(litCounter), identry });
				litCounter++;
			}
			else if (checkChain(words[i].first, typeCharLiteral))
			{
				LT::Entry entry = { LEX_LITERAL, words[i].second };
				LT::Add(lt, entry);
				IT::Entry identry;
				strcpy(identry.id, ("L" + to_string(litCounter)).c_str());
				identry.idxfirstLE = i;
				identry.idtype = IT::L;
				identry.iddatatype = IT::CHAR;
				identry.value.vchar = words[i].first[1];
				ids.push_back({ "L" + to_string(litCounter), identry });
				litCounter++;
			}
			else if (checkChain(words[i].first, typeStringLiteral))
			{
				LT::Entry entry = { LEX_LITERAL, words[i].second };
				LT::Add(lt, entry);
				IT::Entry identry;
				strcpy(identry.id, ("L" + to_string(litCounter)).c_str());
				identry.idxfirstLE = i;
				identry.idtype = IT::L;
				identry.iddatatype = IT::STR;
				strcpy(identry.value.vstr.str, words[i].first.substr(1, words[i].first.length() - 2).c_str());
				identry.value.vstr.len = words[i].first.size() - 2;
				ids.push_back({ "L" + to_string(litCounter), identry });
				litCounter++;
			}
			else if (checkChain(words[i].first, typeNumbLiteral))
			{
				LT::Entry entry = { LEX_LITERAL, words[i].second };
				LT::Add(lt, entry);
				IT::Entry identry;
				strcpy(identry.id, ("L" + to_string(litCounter)).c_str());
				identry.idxfirstLE = i;
				identry.idtype = IT::L;
				identry.iddatatype = IT::INT;
				identry.value.vint = stoi(words[i].first);
				ids.push_back({ "L" + to_string(litCounter), identry });
				litCounter++;
			}
			else if (checkChain(words[i].first, typeIdentificator))
			{
				LT::Entry entry = { LEX_ID, words[i].second };
				LT::Add(lt, entry);
				string buf = words[i].first;
				if (foundIds.count(words[i].first) != 0)
				{
					if (checkChain(words[i - 1].first, typeFunction))
					{
						ERROR_THROW_IN(117, words[i].second, i);
					}
					else
					{
						IT::Entry identry;
						strcpy(identry.id, words[i].first.c_str());
						identry.idxfirstLE = i;
						identry.isPointer = true;
						identry.PointeridxfirstLE = foundIds[words[i].first];
						ids.push_back({ words[i].first, identry });
					}
				}
				else if (foundIds.count(buf.insert(0, functionPrefix.top())) != 0)
				{
					if (checkChain(words[i - 2].first, typeDeclare))
					{
						ERROR_THROW_IN(116, words[i].second, i);
					}
					else
					{
						IT::Entry identry;
						strcpy(identry.id, buf.c_str());
						identry.idxfirstLE = i;
						identry.isPointer = true;
						identry.PointeridxfirstLE = foundIds[buf];
						ids.push_back({ buf, identry });
					}
				}
				else
				{
					string foundIdsBuf = words[i].first;
					if (checkChain(words[i - 1].first, typeFunction))
					{
						foundIds.insert({ words[i].first, i });
						IT::Entry identry;
						identry.isPointer = false;
						identry.idtype = IT::F;
						identry.idxfirstLE = i;
						strcpy(identry.id, words[i].first.c_str());
						if (checkChain(words[i - 2].first, typeInteger))
						{
							identry.iddatatype = IT::INT;
							identry.value.vint = TI_INT_DEFAULT;
						}
						else
						{
							identry.iddatatype = IT::STR;
							identry.value.vstr.len = 0;
							identry.value.vstr.str[0] = TT_STR_DEFAULT;
							identry.value.vstr.str[1] = '\0';
						}
						ids.push_back({ words[i].first, identry });
					}
					else if ((checkChain(words[i + 1].first, typeComma) || checkChain(words[i + 1].first, typeRightThesis)) && !checkChain(words[i - 1].first, typePlus) && !checkChain(words[i - 1].first, typeMinus) && !checkChain(words[i - 1].first, typeRightThesis) && !checkChain(words[i - 1].first, typeMulti) && !checkChain(words[i + 1].first, typeDel))
					{
						foundIdsBuf.insert(0, functionPrefix.top());
						foundIds.insert({ foundIdsBuf, i });
						IT::Entry identry;
						identry.isPointer = false;
						identry.idxfirstLE = i;
						identry.idtype = IT::P;
						strcpy(identry.id, words[i].first.insert(0, functionPrefix.top()).c_str());;
						if (checkChain(words[i - 1].first, typeInteger))
						{
							identry.iddatatype = IT::INT;
						}
						else if (checkChain(words[i - 1].first, typeString))
						{
							identry.iddatatype = IT::STR;
						}
						else if (checkChain(words[i - 1].first, typeBool))
						{
							identry.iddatatype = IT::BOOL;
						}
						else if (checkChain(words[i - 1].first, typeChar))
						{
							identry.iddatatype = IT::CHAR;
						}
						ids.push_back({ words[i].first, identry });
					}
					else if (checkChain(words[i - 2].first, typeDeclare))
					{
						foundIdsBuf.insert(0, functionPrefix.top());
						foundIds.insert({ foundIdsBuf, i });
						IT::Entry identry;
						identry.isPointer = false;
						identry.idtype = IT::V;
						strcpy(identry.id, words[i].first.insert(0, functionPrefix.top()).c_str());
						identry.idxfirstLE = i;
						if (checkChain(words[i - 1].first, typeInteger))
						{
							identry.iddatatype = IT::INT;
							identry.value.vint = TI_INT_DEFAULT;
						}
						else if (checkChain(words[i - 1].first, typeChar))
						{
							identry.iddatatype = IT::CHAR;
							identry.value.vchar = TT_CHAR_DEFAULT;
						}
						else if (checkChain(words[i - 1].first, typeString))
						{
							identry.iddatatype = IT::STR;
							identry.value.vstr.len = 0;
							identry.value.vstr.str[0] = TT_STR_DEFAULT;
						}
						else if (checkChain(words[i - 1].first, typeBool))
						{
							identry.iddatatype = IT::BOOL;
							identry.value.vbool = TT_BOOL_DEFAULT;
						}
						ids.push_back({ words[i].first, identry });
					}
					else
					{
						ERROR_THROW_IN(115, words[i].second, i);
					}
				}
			}
			else if (!checkChain(words[i].first, typeSlashN))
			{
				ERROR_THROW_IN(114, words[i].second, i);
			};
			i++;
		}
		for (int i = 0; i < ids.size(); i++)
		{
			IT::Add(it, ids[i].second);
		}
	};

	bool isSeparator(char symb)
	{
		char check[] = " ,;'(){}[]+-*/=|\n\t";

		for (int i = 0; i < strlen(check); i++)
		{
			if (symb == check[i])
			{
				return true;
			}
		}

		return false;
	}

	bool checkChain(std::string word, FST::FST fst)
	{
		fst.string = word;

		return FST::execute(fst);
	}

	void printLexTable(LT::LexTable lt)
	{
		std::cout << "Таблица лексем:";
		int line = 0;
		for (int i = 0; i < lt.size; i++)
		{
			if (LT::GetEntry(lt, i).sn != line)
			{
				line++;
				std::cout << "\n";
				std::cout << std::setw(2) << std::setfill('0') << line << " ";
				std::cout << LT::GetEntry(lt, i).lexema;
			}
			else
			{
				std::cout << LT::GetEntry(lt, i).lexema;
			}
		}
	}

	void printIdTable(IT::IdTable it)
	{
		std::cout << "\n\nТаблица идентификаторов:\n";
		for (int i = 0; i < it.size; i++)
		{
			if (!it.table[i].isPointer || it.table[i].idtype == 4)
			{
				std::cout << "№: " << i + 1 << "\t" << "idxfirstLE: " << it.table[i].idxfirstLE << "\tИдентификатор: " << it.table[i].id;
			
				if (it.table[i].idtype == 1)
				{
					std::cout << std::setw(6) << "\tТип: Переменная";
					if (it.table[i].iddatatype == 1)
					{
						std::cout << std::setw(15) << "\t\tТип данных: int          " << "\tЗначение: " << it.table[i].value.vint;
					}
					else if (it.table[i].iddatatype == 2)
					{
						std::cout << std::setw(15) << "\t\tТип данных: string        ";
						if (it.table[i].value.vstr.str[0] != TT_STR_DEFAULT)
						{
							std::cout << "\tЗначение: " << it.table[i].value.vstr.str << std::setw(15) << "\t\tДлина строки: " << it.table[i].value.vstr.len;
						}
					}
					else if (it.table[i].iddatatype == 3)
					{
						std::cout << std::setw(15) << "\t\tТип данных: char        ";
						if (it.table[i].value.vchar != TT_CHAR_DEFAULT)
						{
							std::cout << "\tЗначение: " << it.table[i].value.vchar;
						}
					}
					else if (it.table[i].iddatatype == 4)
					{
						std::cout << std::setw(15) << "\t\tТип данных: bool        ";
						std::cout << "\tЗначение: ";
						if (it.table[i].value.vbool)
						{
							std::cout << "true";
						}
						else
						{
							std::cout << "false";
						}
					}
				}
				else if (it.table[i].idtype == 2)
				{
					std::cout << std::setw(6) << "\tТип: Функция\t";
					if (it.table[i].iddatatype == 1)
					{
						std::cout << std::setw(6) << "\tТип данных: int\t";
					}
					else if (it.table[i].iddatatype == 2)
					{
						std::cout << std::setw(6) << "\tТип данных: string\t";
					}
					else if (it.table[i].iddatatype == 3)
					{
						std::cout << std::setw(6) << "\tТип данных: char\t";
					}
					else if (it.table[i].iddatatype == 4)
					{
						std::cout << std::setw(6) << "\tТип данных: bool\t";
					}
					else if (it.table[i].iddatatype == 5)
					{
						std::cout << std::setw(6) << "\tТип данных: void\t";
					}
				}
				else if (it.table[i].idtype == 3)
				{
					std::cout << std::setw(6) << "\tТип: Параметр\t";
					if (it.table[i].iddatatype == 1)
					{
						std::cout << std::setw(6) << "\tТип данных: int\t\t";
					}
					else if (it.table[i].iddatatype == 2)
					{
						std::cout << std::setw(6) << "\tТип данных: string\t\t";
					}
					else if (it.table[i].iddatatype == 3)
					{
						std::cout << std::setw(6) << "\tТип данных: char\t\t";
					}
					else if (it.table[i].iddatatype == 4)
					{
						std::cout << std::setw(6) << "\tТип данных: bool\t\t";
					}
				}
				else if (it.table[i].idtype == 4)
				{
					std::cout << std::setw(6) << "\tТип: Литерал\t";
					if (it.table[i].iddatatype == 1)
					{
						std::cout << std::setw(6) << "\tТип данных: int\t";
						std::cout << std::setw(6) << "\tЗначение: " << it.table[i].value.vint;
					}
					else if (it.table[i].iddatatype == 2)
					{
						std::cout << std::setw(6) << "\tТип данных: string\t";
						std::cout << std::setw(6) << "\tЗначение: " << it.table[i].value.vstr.str << "\tДлина строки: " << it.table[i].value.vstr.len;
					}
					else if (it.table[i].iddatatype == 3)
					{
						std::cout << std::setw(6) << "\tТип данных: char\t";
						std::cout << std::setw(6) << "\tЗначение: " << it.table[i].value.vchar;
					}
					else if (it.table[i].iddatatype == 4)
					{
						std::cout << std::setw(6) << "\tТип данных: bool\t";
						std::cout << std::setw(6) << "\tЗначение: " << (it.table[i].value.vbool ? "true" : "false");
					}
				}
			}
			else
			{
				std::cout << "№: " << i + 1 << "\t" << "idxfirstLE: " << it.table[i].idxfirstLE << "\tУказатель на: " << it.table[i].id;
				if(it.table[i].PointeridxfirstLE != -1)
				{
					std::cout << "(idxfirstLE: " << it.table[i].PointeridxfirstLE << ")";
				}
			}
			std::cout << "\n\n";
		}
	}
}