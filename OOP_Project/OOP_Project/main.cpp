#include <iostream>
#include "Menu.h"
#include <exception>

int main()
{
	try
	{
		menu();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}