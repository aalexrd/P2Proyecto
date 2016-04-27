#include <iostream>
#include <io.h>

void main()
{
	char l;
	for (int i = 0; i < 256; i++)
	{
		l = i;
		std::cout << l << " " << i << std::endl;
	}
	_setmode(_fileno(stdout), 0x20000);
	std::wcout << L"Hello, \u0444!\n";
	system("pause");
}
