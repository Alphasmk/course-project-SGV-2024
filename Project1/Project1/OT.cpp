#include "stdafx.h"
#include "OT.h"

namespace OT
{
    OpTable Create()
    {
        OpTable optable;
        optable.size = 0;
        optable.table = new Operator[250];

        return optable;
    }

    void Add(OpTable& ot, Operator oper)
    {
        ot.table[ot.size] = oper;
        ot.size++;
    }

    Operator GetOperator(OpTable& ot, int n)
    {
        return ot.table[n];
    }

    void Delete(OpTable& ot)
    {
        delete[] ot.table;
        ot.size = 0;
    }

    void Print(OpTable ot, Log::LOG log)
    {
        
        for (int i = 0; i < ot.size; i++)
        {
            *log.stream << "Лексема: ";
            switch (ot.table[i].operatorType)
            {
            case OT::A:
                *log.stream << "+" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::D:
                *log.stream << "/" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::M:
                *log.stream << "*" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::S:
                *log.stream << "-" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::IE:
                *log.stream << "==" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::INE:
                *log.stream << "!=" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::G:
                *log.stream << ">" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::L:
                *log.stream << "<" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::GE:
                *log.stream << ">=" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::LE:
                *log.stream << "<=" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            }
        }
    }
}
