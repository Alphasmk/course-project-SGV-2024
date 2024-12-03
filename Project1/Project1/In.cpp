#include "stdafx.h"

using namespace std;

In::INTAB In::getin(wchar_t infile[], wchar_t outfile[])
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    INTAB in;
    wifstream file(infile);
    if (!file.is_open())
    {
        ERROR_THROW(110);
    }

    in.size = 0;
    in.lines = 0;
    in.ignor = 0;
    in.text = new unsigned char[IN_MAX_LEN_TEXT];

    const int code_table[] = IN_CODE_TABLE;
    for (int i = 0; i < 256; i++)
    {
        in.code[i] = code_table[i];
    }

    wchar_t buf;
    int index = 0;

    while (file.get(buf) && index < IN_MAX_LEN_TEXT - 1)
    {
        if (buf == L'\n')
        {
            in.text[index] = '|';
            in.text[index + 1] = '\n';
            in.lines++;
            index+=2;
        }
        else if (in.code[static_cast<unsigned int>(buf)] == INTAB::F)
        {
            ERROR_THROW_IN(111, in.lines, index);
        }
        else if (in.code[static_cast<unsigned int>(buf)] == INTAB::I)
        {
            in.ignor++;
        }
        else if (in.code[static_cast<unsigned int>(buf)] == INTAB::T)
        {
            in.text[index] = static_cast<unsigned char>(buf);
            index++;
        }
        else
        {
            in.text[index] = static_cast<unsigned char>(in.code[static_cast<unsigned int>(buf)]);
            index++;
        }
    }

    in.text[index] = '\0';
    in.size = index;
    file.close();

    ofstream outfilet(outfile);
    outfilet << in.text;
    outfilet.close();
    return in;
}
