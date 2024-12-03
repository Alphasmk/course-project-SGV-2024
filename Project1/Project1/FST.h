#pragma once
#include "stdafx.h"
#include <cstddef>

namespace FST
{
    struct RELATION      // ребро:символ - > вершина графа перехода конечного автомата
    {
        char symbol;  // символ перехода
        short nnode;  // номер смежной вершины
        RELATION(
            char c = 0x00,    // символ перехода
            short ns = NULL    //новое состояние
        );
    };
    struct NODE  // вершина графа перехода
    {
        short n_relation;  // количество инциндентных ребер
        RELATION* relations;  // инциндентные ребра
        NODE();
        NODE(
            short n,    // количество инциндентных ребёр
            RELATION rel, ...  //список ребер
        );
    };
    struct FST  // недетерминированный конечный автомат
    {
        std::string string;    // цепочка (строка, завершается 0x00)
        short position;    // текущая позиция в строке
        short nstates;    // количество состояний автомата
        NODE* nodes;    // граф переходов: [0] - начальное состояние, [nstate - 1] - конечное
        short* rstates;    // возможные состояния автомата на данной позиции
        FST(
            std::string s,    // цепочка (строка, завершается 0x00)
            short ns,    // количество состояний автомата
            NODE n, ...    // список состояний (граф переходов)
        );
    };
    bool execute(      // выполнить распознавание цепочки
        FST& fst      // недетерминированный конечный автомат
    );

}
