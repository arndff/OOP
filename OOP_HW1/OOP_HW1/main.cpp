#include "CarsDB.h"
#include <exception>

int main()
{
	try
	{
		menu();
	}
	catch (std::exception& e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}
