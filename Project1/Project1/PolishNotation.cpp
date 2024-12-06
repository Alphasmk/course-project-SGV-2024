#include "stdafx.h"
#include "PolishNotation.h"

namespace PolishNotation
{
	int checkPriority(char symb)
	{
		switch (symb)
		{
		case '(':
		case ')':
			return 0;
			break;
		case '+':
		case '-':
			return 1;
			break;
		case '*':
		case '/':
			return 2;
			break;
		default:
			return -1;
		}
	}

    void PolishNotation(int iter, IT::IdTable& it, LT::LexTable& lt)
    {
		stack<LT::Entry> symbStack;
		LT::Entry outstr[200];
		int j = 0;
		int iterBuf = iter;
		bool isFunction = false;
		int paramCounter = 0, len = 0, lenout = 0, semicolonid, hesis = 0;

        // Определяем индекс точки с запятой (;) и длину выражения
		for (int i = iter; lt.table[i].lexema != ';'; i++)
		{
			len = i;
			semicolonid = i + 1;
		}
		while (lt.table[iter].lexema != ';')
		{
			if (isSeparator(lt.table[iter].lexema) && !isFunction)
			{
				if (lt.table[iter].lexema == ')')
				{
					while (true)
					{
						if (symbStack.top().lexema == '(')
						{
							symbStack.pop();
							break;
						}
						else if (symbStack.top().lexema == ')')
						{
							symbStack.pop();
						}
						else
						{
							outstr[lenout++] = symbStack.top();
							symbStack.pop();
						}
					}
					hesis++;
				}
				else if (!symbStack.empty() && checkPriority(lt.table[iter].lexema) <= checkPriority(symbStack.top().lexema) && lt.table[iter].lexema != '(')
				{
					while (!symbStack.empty() && checkPriority(symbStack.top().lexema) >= checkPriority(lt.table[iter].lexema))
					{
						outstr[lenout++] = symbStack.top();
						symbStack.pop();
					}
					symbStack.push(lt.table[iter]);
				}
				else if (lt.table[iter].lexema == '(')
				{
					symbStack.push(lt.table[iter]);
					hesis++;
				}
				else
				{
					symbStack.push(lt.table[iter]);
				}
			}
			else if (isFunction)
			{
				if (lt.table[iter].lexema != ',' && lt.table[iter].lexema != ')')
				{
					if (lt.table[iter].lexema == '(')
					{
						symbStack.push(lt.table[iter]);
						hesis++;
					}
					else
					{
						outstr[lenout++] = lt.table[iter];
						paramCounter++;
					}
				}
				else if (lt.table[iter].lexema == ')')
				{
					hesis++;
					LT::Entry entry;
					entry.lexema = '0' + paramCounter;
					entry.sn = lt.table[iter].sn;
					symbStack.push(entry);
					entry.lexema = '@';
					entry.sn = lt.table[iter].sn;
					symbStack.push(entry);
					while (true)
					{
						outstr[lenout++] = symbStack.top();
						symbStack.pop();
						if (symbStack.top().lexema == '(')
						{
							symbStack.pop();
							isFunction = false;
							break;
						}
					}
				}
				else if (lt.table[iter].lexema == ',')
				{
					hesis++;
				}
			}
			else
			{
				if (lt.table[iter].idxTI != 0 && it.table[lt.table[iter].idxTI - 1].idtype == IT::F)
				{
					isFunction = true;
				}
				outstr[lenout++] = lt.table[iter];
			}
			iter++;
			if (lt.table[iter].lexema == ';')
			{
				if (!symbStack.empty())
				{
					while (!symbStack.empty())
					{
						outstr[lenout++] = symbStack.top();
						symbStack.pop();
					}
				}
			}
		}

        // Переносим оставшиеся элементы из стека в выходной массив
        while (!symbStack.empty())
        {
            outstr[lenout++] = symbStack.top();
            symbStack.pop();
        }

        // Записываем результат обратно в таблицу `lt`
		// Записываем результат обратно в таблицу `lt`
		for (int i = 0; i < lenout; i++)
		{
			lt.table[iterBuf + i] = outstr[i]; // Копируем лексемы из выходного массива
		}

		// Добавляем точку с запятой
		lt.table[iterBuf + lenout] = lt.table[semicolonid];

		// Очищаем оставшиеся места, чтобы не было лишних символов
		for (int i = iterBuf + lenout + 1; i <= semicolonid; i++) // <= semicolonid для захвата всех остатков
		{
			lt.table[i].lexema = '~';      // Заменяем остаточные элементы символом `~`
			lt.table[i].sn = lt.table[semicolonid].sn; // Обновляем номер строки, если нужно
			lt.table[i].idxTI = -1;        // Сбрасываем индекс идентификатора, если нужно
		}
    }


	bool isSeparator(char symb)
	{
		char check[] = ",()+-*/";

		for (int i = 0; i < strlen(check); i++)
		{
			if (symb == check[i])
			{
				return true;
			}
		}

		return false;
	}
}
