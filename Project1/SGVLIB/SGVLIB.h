#pragma once
extern "C" {
	int __stdcall _exp(int x);
	void __stdcall _pause();
	int __stdcall _pow(int a, int b);
	void __stdcall _printInt(const int value);
	void __stdcall _printStr(char* value);
	void __stdcall _printBool(const bool value);
	void __stdcall _printChar(const char value);
}