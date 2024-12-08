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

    void Print(OpTable ot)
    {
        for (int i = 0; i < ot.size; i++)
        {
            cout << "Лексема: ";
            switch (ot.table[i].operatorType)
            {
            case OT::A:
                cout << "+" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::D:
                cout << "/" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::M:
                cout << "*" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::S:
                cout << "-" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::IE:
                cout << "==" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::INE:
                cout << "!=" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::G:
                cout << ">" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::L:
                cout << "<" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::GE:
                cout << ">=" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            case OT::LE:
                cout << "<=" << "\tИндекс в таблице лексем: " << ot.table[i].idxLE << endl;
                break;
            }
        }
    }
}
