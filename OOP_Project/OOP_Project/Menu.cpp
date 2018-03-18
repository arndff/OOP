#include "Menu.h"

void normalizeFilePath(char * path)
{
	size_t pathLen = strlen(path);
	for (size_t i = 0; i < pathLen; ++i)
	{
		if (path[i] == '\\')
		{
			path[i] = '/';
		}
	}
}

size_t args(const char * cmd)
{
	size_t cmdLen = strlen(cmd);
	size_t cnt = 0;
	for (size_t i = 0; i < cmdLen; ++i)
	{
		if (cmd[i] == ' ')
		{
			++cnt;
		}
	}

	return ++cnt;
}

char ** cmdToArray(const char * cmd, size_t& sz)
{
	char ** arr;
	size_t cmdArgs = args(cmd);
	allocate(arr, cmdArgs);

	size_t cmdLen = strlen(cmd);
	size_t currWordLen = 0;
	
	for (size_t i = 0, j = 0; i < cmdLen + 1; )
	{
		if (cmd[i] != ' ' && i != cmdLen)
		{
			++currWordLen;
			++i;
		}
		else
		{
			i -= currWordLen;

			allocate(arr[j], currWordLen + 1);

			for (size_t k = 0; k < currWordLen; ++k)
			{
				arr[j][k] = cmd[i++];
			}

			arr[j++][currWordLen] = '\0';

			currWordLen = 0;
			++i;
		}
	}

	sz = cmdArgs;
	return arr;
}

int parseFileCmd(const char * cmd, char * path)
{
	size_t size = 0;
	char ** arr = cmdToArray(cmd, size);

	if (strcmp(arr[0], "open") == 0 && size == 2)
	{
		normalizeFilePath(arr[1]);
		strcpy(path, arr[1]);
		free(arr, size);

		return 0;
	}
	else if (strcmp(arr[0], "close") == 0 && size == 1)
	{
		free(arr, size);

		return 1;
	}
	else if (strcmp(arr[0], "save") == 0 && size == 1)
	{
		free(arr, size);

		return 2;
	}
	else if (strcmp(arr[0], "saveas") == 0 && size == 2)
	{
		normalizeFilePath(arr[1]);
		strcpy(path, arr[1]);
		free(arr, size);

		return 3;
	}
	else
	{
		free(arr, size);

		return -1;
	}
}

void fileUtils(API& obj)
{
	char cmd[CMD_LEN + 1];
	char path[PATH_LEN + 1];

	int choice;
	while (true)
	{
		std::cout << "1.1 open\n";
		std::cout << "1.2 save\n";
		std::cout << "1.3 save As...\n";
		std::cout << "1.4 close...\n\n";
		std::cout << "enter your command: ";

		memset(cmd, 0, CMD_LEN);
		memset(path, 0, PATH_LEN);

		std::cin.getline(cmd, CMD_LEN);
		choice = parseFileCmd(cmd, path);

		switch (choice)
		{
			case 0:
				return obj.open(path);
			case 1:
				return obj.close();
			case 2:
				return obj.save();
			case 3:
				return obj.saveAs(path);
			default: 
				std::cout << "Wrong input\n"; break; //should never reach this line
		}
	}
}

void createCmd(char ** arr, size_t size, API& obj)
{
	if (strcmp("rectangle", arr[1]) == 0 && size == 7)
	{
		double x = std::stod(arr[2]),
			   y = std::stod(arr[3]);
		
		if (x < 0) x *= -1;
		if (y < 0) y *= -1;

		Point bl(x, y);
		Rectangle r(arr[6], bl, std::stod(arr[4]), std::stod(arr[5]));
		obj.create(&r);
	}
	else if (strcmp("circle", arr[1]) == 0 && size == 6)
	{
		double x = std::stod(arr[2]),
		       y = std::stod(arr[3]);
		
		if (x < 0) x *= -1;
		if (y < 0) y *= -1;
		
		Point center(x, y);
		Circle c(arr[5], center, std::stod(arr[4]));
		obj.create(&c);
	}
	else if (strcmp("line", arr[1]) == 0 && size == 7)
	{
		double x1 = std::stod(arr[2]),
			   y1 = std::stod(arr[3]),
			   x2 = std::stod(arr[4]),
			   y2 = std::stod(arr[5]);
		
		if (x1 < 0) x1 *= -1;
		if (y1 < 0) y1 *= -1;
		if (x2 < 0) x2 *= -1;
		if (y2 < 0) y2 *= -1;
		
		Point a(x1, y1);
		Point b(x2, y2);
		Line l(arr[6], a, b);
		obj.create(&l);
	}
}

void translateCmd(char ** arr, size_t size, API& obj)
{
	double a = 0, b = 0;
	char * side;
	size_t sideLen = 0;
	for (size_t i = 1; i < 3; ++i)
	{
		size_t currLen = strlen(arr[i]);
		for (size_t j = currLen - 1; ; --j)
		{
			if (arr[i][j] != '=')
			{
				++sideLen;
			}
			else
			{
				break;
			}
		}

		allocate(side, sideLen + 1);

		memset(side, 0, sideLen + 1);

		for (size_t j = currLen - sideLen, k = 0; j < currLen; ++j, ++k)
		{
			side[k] = arr[i][j];
		}

		side[sideLen] = '\0';
		sideLen = 0;

		if (a == 0)
		{
			a = std::stod(side);
		}
		else
		{
			b = std::stod(side);
		}
	}

	delete[] side;

	Point vec(b, a);

	if (size == 3)
	{
		obj.translate(vec);
	}
	else if (size == 4)
	{
		obj.translate(vec, std::stoi(arr[3]));
	}
}

void withinCmd(char ** arr, size_t size, API& obj)
{
	if (strcmp("circle", arr[1]) == 0 && size == 5)
	{
		Point center(std::stod(arr[2]), std::stod(arr[3]));
		obj.within(center, std::stod(arr[4]));
	}
	else if (strcmp("rectangle", arr[1]) == 0 && size == 6)
	{
		Point bl(std::stod(arr[2]), std::stod(arr[3]));
		obj.within(bl, std::stod(arr[4]), std::stod(arr[5]));
	}
}

void parseFigCmd(const char * cmd, API& obj)
{
	size_t size;
	char ** arr = cmdToArray(cmd, size);
	
	if (strcmp("print", arr[0]) == 0 && size == 1)
	{
		obj.print();
	}
	else if (strcmp("erase", arr[0]) == 0 && size == 2)
	{
		size_t idx = std::stoi(arr[1]);
		obj.erase(idx);
	}
	else if (strcmp("create", arr[0]) == 0)
	{
		createCmd(arr, size, obj);
	}
	else if (strcmp("translate", arr[0]) == 0)
	{
		translateCmd(arr, size, obj);
	}
	else if (strcmp("within", arr[0]) == 0)
	{
		withinCmd(arr, size, obj);
	}

	free(arr, size);
}

void menu()
{
	API api;
	char cmd[CMD_LEN + 1];

	while (true)
	{
		std::cout << "1. file\n";
		std::cout << "   1.1 open\n";
		std::cout << "   1.2 save\n";
		std::cout << "   1.3 save As...\n";
		std::cout << "   1.4 close\n";
		std::cout << "2. print\n";
		std::cout << "3. create\n";
		std::cout << "4. erase\n";
		std::cout << "5. translate\n";
		std::cout << "6. within\n";
		std::cout << "7. exit\n\n";

		memset(cmd, 0, CMD_LEN + 1);
		std::cout << "enter your command: ";
		std::cin.getline(cmd, CMD_LEN);

		if (strcmp(cmd, "file") == 0)
		{
			fileUtils(api);
		}
		else if (strcmp(cmd, "exit") == 0)
		{
			break;
		}
		else
		{
			parseFigCmd(cmd, api);
		}
	}
}