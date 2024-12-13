#include "stdafx.h"
#include "CodeGeneration.h"
#include <queue>
namespace CG
{
	Generator::Generator(LT::LexTable _lt, IT::IdTable _it, OT::OpTable _ot)
	{
		lt = _lt;
		it = _it;
		ot = _ot;
		out = std::ofstream("E:\\уник\\КурсачКПО\\Project1\\SGVASM\\asm.asm");
		Head();
		Constants();
		Data();
		Code();
	}

	void Generator::Head()
	{
		out << ".586\n";
		out << "\t.model flat, stdcall\n";
		out << "\tincludelib libucrt.lib\n";
		out << "\tincludelib kernel32.lib\n";
		out << "\tExitProcess PROTO :DWORD\n\n";
		out << "\t_exp PROTO :DWORD\n";
		out << "\t_pow PROTO :DWORD, :DWORD\n";
		out << "\t_printInt PROTO :DWORD\n";
		out << "\t_printStr PROTO :DWORD\n";
		out << "\t_printBool PROTO :DWORD\n";
		out << "\t_printChar PROTO :DWORD\n";
		out << "\t_pause PROTO\n";
		out << "\n.stack 4096\n";
	}

	void Generator::Constants()
	{
		out << ".CONST\n";
		out << "\tnull_division BYTE \'ERROR: DIVISION BY ZERO\', 0\n";
		out << "\tOVER_FLOW BYTE \'ERROR: OVERFLOW\', 0\n";
		out << "\ttrue BYTE \"true\", 0\n";
		out << "\tfalse BYTE \"false\", 0\n";

		out << "\tempty_string BYTE 0\n";
		for (int i = 0; i < it.size; i++)
		{
			if (it.table[i].idtype == IT::L)
			{
				out << "\t" << it.table[i].id;
				if (it.table[i].iddatatype == IT::STR)
				{
					out << " BYTE \"" << it.table[i].value.vstr.str << "\", 0\n";
				}
				else if (it.table[i].iddatatype == IT::INT)
				{
					out << " DWORD " << it.table[i].value.vint << endl;
				}
				else if (it.table[i].iddatatype == IT::CHAR)
				{
					out << " DWORD \'" << it.table[i].value.vchar << "\'\n";
				}
				else
				{
					out << " DWORD " << it.table[i].value.vbool << endl;
				}
			}
		}
	}

	void Generator::Data()
	{
		out << ".DATA\n";
		for (int i = 0; i < lt.size; i++)
		{
			if (lt.table[i].lexema == 'd')
			{
				if (it.table[lt.table[i + 2].idxTI - 1].idtype == IT::V)
				{
					out << "\t" << it.table[lt.table[i + 2].idxTI - 1].id;
					if (it.table[lt.table[i + 2].idxTI - 1].iddatatype == IT::INT)
					{
						out << " DWORD " << it.table[lt.table[i + 2].idxTI - 1].value.vint;
					}
					if (it.table[lt.table[i + 2].idxTI - 1].iddatatype == IT::STR)
					{
						out << " DWORD empty_string";
					}
					if (it.table[lt.table[i + 2].idxTI - 1].iddatatype == IT::CHAR)
					{
						out << " DWORD 0";
					}
					if (it.table[lt.table[i + 2].idxTI - 1].iddatatype == IT::BOOL)
					{
						out << " DWORD  0";
					}
					out << "\n";
				}
			}
		}
	}

	void Generator::Code()
	{
		out << "\n.CODE\n";
		stack<int> stk;
		stack<int> ifi;
		int indOfFunc = 0;
		int rhesis = -1;
		int num_of_ret = 0; //
		int num_of_if = 0; //
		int num_of_logical = 0;//
		int num_of_boolCompare = 0; //
		int ifCounter = 0;
		string func_name = "";
		bool flag_func = false;//
		bool flag_return = false;//
		bool flag_main = false;//
		bool flag_if = false;//
		bool flag_else = false;//
		for (int i = 0; i < lt.size; i++)
		{
			if (lt.table[i].lexema == 'f')
			{
				indOfFunc = i + 1;
				out << it.table[lt.table[indOfFunc].idxTI - 1].id << " PROC ";
				func_name = it.table[lt.table[indOfFunc].idxTI - 1].id;

				while (lt.table[i].lexema != ')')
				{
					rhesis = i;
					i++;
				}

				while (lt.table[i].lexema != '(')
				{
					if (lt.table[i].lexema == 'i')
					{
						out << it.table[lt.table[i].idxTI - 1].id << ":DWORD";
						if (lt.table[i - 2].lexema != '(')
						{
							out << ", ";
						}
					}
					i--;
				}
				flag_func = true;
				i = rhesis;
				out << "\n";
			}
			if (lt.table[i].lexema == 'm')
			{
				flag_main = true;
				out << "main PROC\n";
			}
			if (lt.table[i].lexema == '=')
			{
				int result_position = i - 1;
				while (lt.table[i].lexema != ';')
				{
					if ((static_cast<int>(lt.table[i].lexema) > 57 || static_cast<int>(lt.table[i].lexema) < 48) && lt.table[i].lexema != '@')
					{
						int func_id = 0;
						if (lt.table[i].lexema == 'l')
						{
							if (it.table[lt.table[i].idxTI - 1].iddatatype == IT::STR)
							{
								out << "\push offset " << it.table[lt.table[i].idxTI - 1].id << endl;
							}
							else
							{
								out << "\tpush " << it.table[lt.table[i].idxTI - 1].id << endl;
							}
						}
						else if (lt.table[i].lexema == 'i')
						{
							if (it.table[lt.table[i].idxTI - 1].idtype == IT::F)
							{
								int r = 0;
								int l = 0;
								l = i;
								i++;
								r = i;
								while (lt.table[i].lexema != '@')
								{
									r = i;
									i++;
								}
								i++;
								while (r != l)
								{
									if (lt.table[r].lexema == 'i' || lt.table[r].lexema == 'l')
									{
										out << "\tpush " << it.table[lt.table[r].idxTI - 1].id << endl;
									}
									r--;
								}
								out << "\tcall " << it.table[lt.table[r].idxTI - 1].id << "\n\tpush eax\n";
							}
							else
							{
								out << "\tpush " << it.table[lt.table[i].idxTI - 1].id << endl;
							}
						}
						else if (lt.table[i].lexema == 'v')
						{
							if (ot.table[lt.table[i].idxOP].operatorType == OT::M)
							{
								out << "\tpop eax\n\tpop ebx\n";
								out << "\tmul ebx\n\tpush eax\n";
							}
							else if (ot.table[lt.table[i].idxOP].operatorType == OT::A)
							{
								out << "\tpop eax\n\tpop ebx\n";
								out << "\tadd eax, ebx\n\tpush eax\n";
							}
							else if (ot.table[lt.table[i].idxOP].operatorType == OT::S)
							{
								out << "\tpop ebx\n\tpop eax\n";
								out << "\tsub eax, ebx\n\tpush eax\n";
							}
							else if (ot.table[lt.table[i].idxOP].operatorType == OT::D)
							{
								out << "\tpop ebx\n\tpop eax\n";
								out << "\tcmp ebx,0\n"\
									"\tje SOMETHINGWRONG\n";
								out << "\tcdq\n";
								out << "\tdiv ebx\n\tpush eax\n";
							}
						}
					}
					i++;
				}
				if (it.table[lt.table[result_position].idxTI - 1].iddatatype == IT::INT)
				{
					out << "\tpop eax\n";
					out << "\tcmp eax, 255\n";
					out << "\tjg overflow\n";
					out << "\tcmp eax, 0\n";
					out << "\tjl overflow\n";
					out << "\tmov " << it.table[lt.table[result_position].idxTI - 1].id << ", eax";
				}
				else if(it.table[lt.table[result_position].idxTI - 1].idtype != IT::F)
				{
					out << "\tpop " << it.table[lt.table[result_position].idxTI - 1].id << "\n";
				}
				out << endl;
			}
			else if (lt.table[i].lexema == 'r')
			{
				out << "\tpush ";
				i++;
				if (it.table[lt.table[i].idxTI - 1].iddatatype == IT::STR)
				{
					out << "OFFSET " << it.table[lt.table[i++].idxTI - 1].id << endl;
				}
				else if (it.table[lt.table[i].idxTI - 1].iddatatype == IT::INT)
				{
					out << it.table[lt.table[i++].idxTI - 1].id << endl;
				}
				else if (it.table[lt.table[i].idxTI - 1].iddatatype == IT::BOOL)
				{
					out << it.table[lt.table[i++].idxTI - 1].id << endl;
				}
				else if (it.table[lt.table[i].idxTI - 1].iddatatype == IT::CHAR)
				{
					out << "\'" << it.table[lt.table[i++].idxTI - 1].id << "\'" << endl;
				}
				if (flag_func)
				{
					out << "\tjmp local" << num_of_ret << endl;
					flag_return = true;
				}
				if (flag_main)
				{
					out << "\tjmp theend\n";
					flag_return = true;
				}
			}
			else if (lt.table[i].lexema == '}')
			{
				ifCounter--;
				if (flag_main && !flag_func && lt.table[i + 1].lexema == ';')
				{
					if (flag_return)
					{
						flag_return = false;
					}
				}
				if (flag_func && lt.table[i + 1].lexema == ';' && ifCounter == 0)
				{
					if (flag_return)
					{
						out << "local" << num_of_ret++ << ":\n";
						out << "\tpop eax\n\tret\n";
						flag_return = false;
					}
					out << func_name << " ENDP\n\n";
					flag_func = false;
				}
				if (!stk.empty())
				{
					if (stk.top() == 1)
					{
						if (lt.table[i + 1].lexema == 's')
						{
							out << "\tjmp ifEnd" << ifi.top() << endl;
						}
						else
						{
							out << "else" << ifi.top() << ":\n";
						}
						stk.pop();
					}
					else if (stk.top() == 2)
					{
						out << "ifEnd" << ifi.top() << ":\n";
						ifi.pop();
						flag_else = false;
						stk.pop();
					}
				}
			}
			else if (lt.table[i].lexema == '{')
			{
				ifCounter++;
				if (num_of_if && !flag_else && flag_if)
				{
					out << "ifi" << ifi.top() << ":\n";
					flag_if = false;
				}
			}
			else if (lt.table[i].lexema == 's')
			{
				flag_if = true;
				stk.push(1);
				num_of_if++;
				ifi.push(num_of_if);
			}
			else if (lt.table[i].lexema == 'e')
			{
				flag_else = true;
				stk.push(2);
			}
			else if (lt.table[i].lexema == LEX_LEFTHESIS)
			{
				if (num_of_if && lt.table[i - 1].lexema == 's')
				{
					out << "\tmov eax, " << it.table[lt.table[i + 1].idxTI - 1].id << endl;
					out << "\tcmp eax, " << it.table[lt.table[i + 3].idxTI - 1].id << endl;
					if (ot.table[lt.table[i + 2].idxOP].operatorType == OT::G)
					{
						out << "\tjg ifi" << num_of_if << endl;
						out << "\tjle else" << num_of_if << endl;
					}
					else if (ot.table[lt.table[i + 2].idxOP].operatorType == OT::L)
					{
						out << "\tjl ifi" << num_of_if << endl;
						out << "\tjge else" << num_of_if << endl;
					}
					else if (ot.table[lt.table[i + 2].idxOP].operatorType == OT::IE)
					{
						out << "\tjz ifi" << num_of_if << endl;
						out << "\tjnz else" << num_of_if << endl;
					}
					else if (ot.table[lt.table[i + 2].idxOP].operatorType == OT::INE)
					{
						out << "\tjnz ifi" << num_of_if << endl;
						out << "\tjz else" << num_of_if << endl;
					}
					else if (ot.table[lt.table[i + 2].idxOP].operatorType == OT::GE)
					{
						out << "\tjge ifi" << num_of_if << endl;
						out << "\tjl else" << num_of_if << endl;
					}
					else if (ot.table[lt.table[i + 2].idxOP].operatorType == OT::LE)
					{
						out << "\tjle ifi" << num_of_if << endl;
						out << "\tjg else" << num_of_if << endl;
					}
				}
			}
			else if (lt.table[i].lexema == LEX_PRINT)
			{
				if (it.table[lt.table[i].idxTI - 1].idtype == IT::F && strcmp(it.table[lt.table[i].idxTI - 1].id, "_printInt") == 0)
				{
					out << "\npush " << it.table[lt.table[i + 2].idxTI - 1].id << "\ncall " << it.table[lt.table[i].idxTI - 1].id << "\n";
				}
				else if (it.table[lt.table[i].idxTI - 1].idtype == IT::F && strcmp(it.table[lt.table[i].idxTI - 1].id, "_printStr") == 0)
				{
					if (it.table[lt.table[i + 2].idxTI - 1].iddatatype == IT::STR && (it.table[lt.table[i + 2].idxTI - 1].id[0] == 'L'))
					{
						out << "\npush offset " << it.table[lt.table[i + 2].idxTI - 1].id << "\ncall " << it.table[lt.table[i].idxTI - 1].id << "\n";
					}
					else if(it.table[lt.table[i + 2].idxTI - 1].iddatatype == IT::STR)
					{
						out << "\npush " << it.table[lt.table[i + 2].idxTI - 1].id << "\ncall " << it.table[lt.table[i].idxTI - 1].id << "\n";
					}
					else if ((it.table[lt.table[i + 2].idxTI - 1].iddatatype == IT::CHAR))
					{
						out << "\npush " << it.table[lt.table[i + 2].idxTI - 1].id << "\ncall " << it.table[lt.table[i].idxTI - 1].id << "\n";
					}
				}
				else if (strcmp(it.table[lt.table[i].idxTI - 1].id, "_printChar") == 0)
				{
					out << "\npush " << it.table[lt.table[i + 2].idxTI - 1].id << "\ncall " << it.table[lt.table[i].idxTI - 1].id << "\n";
				}
				else if (strcmp(it.table[lt.table[i].idxTI - 1].id, "_printBool") == 0)
				{
					out << "\npush " << it.table[lt.table[i + 2].idxTI - 1].id << "\ncall " << it.table[lt.table[i].idxTI - 1].id << "\n";
				}
			}
			//else if (it.table[lt.table[i].idxTI - 1].idtype == IT::F && strcmp(it.table[lt.table[i].idxTI - 1].id, "_printBool"))
			//{
			//	out << "\npush" << it.table[lt.table[i + 2].idxTI - 1].id << "\ncall " << it.table[lt.table[i].idxTI - 1].id;
			//}
		}
		out << "\njmp theend";
		out << "\nSOMETHINGWRONG::";
		out << "\n\tpush offset null_division";
		out << "\n\tcall _printStr";
		out << "\njmp THEEND";
		out << "\nTHEEND:";
		out << "\n\tcall _pause";
		out << "\n\tpop eax";
		out << "\n\tret";
		out << "\n\tcall ExitProcess";
		out << "\noverflow::";
		out << "\n\tpush offset OVER_FLOW";
		out << "\n\tcall _printStr";
		out << "\nmain ENDP\nend main";
	}
}