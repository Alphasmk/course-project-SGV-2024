#include <corecrt_math.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
extern "C" {
	int __stdcall _exp(int x)
	{
		int result = pow(2.71828182845, x);
		if (result < 0)
		{
			return 0;
		}
		else if (result > 255)
		{
			return 255;
		}
		else
		{
			return result;
		}
	}

	void __stdcall _pause() {
		system("pause");
	}

	int __stdcall _pow(int a, int b) {
		int result = pow(a, b);
		if (result < 0)
		{
			return 0;
		}
		else if (result > 255)
		{
			return 255;
		}
		else
		{
			return result;
		}
	}

	void __stdcall _printInt(const int value) {
		std::cout << value << std::endl;
	}

	void __stdcall _printStr(char* value) {
		setlocale(LC_ALL, "Rus");
		if (value == nullptr)
		{
			std::cout << std::endl;
			return;
		}
		for (int i = 0; value[i] != '\0'; i++)
		{
			std::cout << value[i];
		}
		std::cout << "\n";
	}

	void __stdcall _printBool(const bool value)
	{
		std::cout << (value ? "true" : "false") << std::endl;
	}

	void __stdcall _printChar(const char value)
	{
		std::cout << value << std::endl;
	}
}
