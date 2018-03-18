#include "CarsDB.h"

//helper functions for addEntry()
int readID()
{
	int id = 0;

	do
	{
		cout << "Enter an ID: ";
		cin >> id;
	} while (id < 0 || id > 3);

	return id;
}

int readReg()
{
	int reg = 0;

	do
	{
		cout << "Enter a reg number: ";
		cin >> reg;
	} while (reg < 1000 || reg > 9999);

	return reg;
}

bool isRegAvailable(int reg)
{
	ifstream file("db-save.dat", ios::binary);
	if (!file) 
	{ 
		throw std::runtime_error("Problem with the file.\n"); 
	}

	Person buff;
	
	while (file.read((char*)&buff, sizeof(buff)))
	{
		if (buff.reg == reg)
		{
			file.close();
			return false;
		}
	}

	file.close();
	return true;
}

bool isFileAvailable()
{
	ifstream input("db-save.dat", ios::binary);
	if (!input)
	{
		return false;
	}
	
	input.close();
	return true;
}

void savePerson(const char* name, int reg, int id)
{
	Person p(name, id, reg);
	
	ofstream output("db-save.dat", ios::binary | ios::app);
	if (!output) 
	{
		throw std::runtime_error("Problem with the file.\n");
	}

	output.write((const char *)&p, sizeof(p));
	output.close();
}

void addEntry()
{
	char name[MAX_LEN+1];
	int reg = 0, id = 0;

	cout << "Enter person's name: ";
	cin.getline(name, MAX_LEN);

	id = readID();
	reg = readReg();

	if (isFileAvailable())
	{
		if (isRegAvailable(reg))
		{
			savePerson(name, reg, id);
		}
		else
		{
			cout << "This registration number is NOT available!\n";
			return;
		}
	}
	else
	{
		savePerson(name, reg, id);
	}
}

//helper function for avgHp()
int getHp(int idx)
{
	switch (idx)
	{
		case 0: return cars[0].hp;
		case 1: return cars[1].hp;
		case 2: return cars[2].hp;
		case 3: return cars[3].hp;
		default: return 0;
	}
}

double avgHp()
{
	ifstream input("db-save.dat", ios::binary);
	if (!input) 
	{ 
		throw std::runtime_error("Problem with the file.\n");
	}

	Person buff;
	double total = 0;
	size_t cnt = 0;

	while (input.read((char*)& buff, sizeof(buff)))
	{
		total += getHp(buff.id);
		++cnt;
	}

	input.close();

	return total / cnt;
}

//helper function for mostPopularCar()
const char * getName(int idx)
{
	switch (idx)
	{
		case 0: return cars[0].car;
		case 1: return cars[1].car;
		case 2: return cars[2].car;
		case 3: return cars[3].car;
		default: return nullptr;
	}
}

int findMax(int* array)
{
	int max = 0;

	for (int i = 1; i < CARS_COUNT; ++i)
	{
		if (array[i] > array[max])
		{
			max = i;
		}
	}

	return max;
}

const char * mostPopularCar()
{
	ifstream input("db-save.dat", ios::in | ios::binary);
	if (!input) 
	{
		throw std::runtime_error("Problem with the file.\n");
	}

	Person buff;
	int cnt[CARS_COUNT] = { 0, };
	
	while (input.read((char *)&buff, sizeof(buff)))
	{
		++cnt[buff.id];
	}

	input.close();

	int max = findMax(cnt);
	
	assert(getName(max));

	char * hype = new char[strlen(getName(max)) + 1];
	strcpy(hype, getName(max));

	return hype;
}

//helper functions for processOwners()
void countEntries(size_t& size)
{
	ifstream input("db-save.dat", ios::binary);
	if (!input) 
	{ 
		throw std::runtime_error("Problem with the file.\n");
	}

	input.seekg(0, ios::end);
	size = input.tellg() / sizeof(Person);

	input.close();
}

void toArray(Person*& entries)
{
	ifstream input("db-save.dat", ios::binary);
	if (!input)
	{ 
		throw std::runtime_error("Problem with the file.\n");
	}

	Person buff;
	int i = 0;
	
	while (input.read((char*)&buff, sizeof(buff)))
	{
		entries[i++] = buff;
	}

	input.close();
}

bool isSaved(const char * person, char ** names, size_t sz)
{
	for (size_t i = 0; i < sz; ++i)
	{
		if (strcmp(person, names[i]) == 0)
		{
			return true;
		}
	}

	return false;
}

void processOwnersHelper(Person*& entries, char **& names, size_t size)
{
	ofstream output("car-report.txt", ios::app);
	if (!output) 
	{ 
		throw std::runtime_error("Problem with the file.\n");
	}

	int curr_total = 0;
	int k = 0; //a counter for the names array

	output << "\n(Person : Total HP)\n\n";

	for (size_t i = 0; i < size; ++i)
	{
		curr_total = 0;

		if (!isSaved(entries[i].name, names, size))
		{
			strcpy(names[k++], entries[i].name);
			curr_total = getHp(entries[i].id);

			for (size_t j = i + 1; j < size; ++j)
			{
				if (strcmp(entries[i].name, entries[j].name) == 0)
				{
					curr_total += getHp(entries[j].id);
				}
			}

			//save to file
			output << entries[i].name << " : " << curr_total << "\n";
		}
	}

	output.close();
}

void processOwners()
{
	size_t size = 0;
	countEntries(size);
	Person * entries = new Person[size];

	toArray(entries);

	char ** names = new char*[size];

	for (size_t i = 0; i < size; ++i)
	{
		names[i] = new(nothrow) char[MAX_LEN];
		if (!names[i])
		{
			for (size_t j = 0; j < i; ++j)
			{
				delete[] names[j];
			}

			delete[] names;
			cout << "Memory allocation problem!\n";
			return;
		}

		strcpy(names[i], "");
	}

	processOwnersHelper(entries, names, size);

	//free memory
	for (size_t i = 0; i < size; ++i)
	{
		delete[] names[i];
	}

	delete[] names;
	delete[] entries;
}

void report()
{
	ofstream output("car-report.txt", ios::trunc);
	if (!output) 
	{ 
		throw std::runtime_error("Problem with the file.\n");
	}

	output << "Average HP: " << avgHp() << "\n";
	output << "The most popular car is: " << mostPopularCar() << "\n";

	output.close();

	processOwners();
}

void clear()
{
	ofstream file("db-save.dat", ios::trunc);
	if (!file) 
	{ 
		throw std::runtime_error("Problem with the file.\n");
	}

	file.close();
}

void menu()
{
	int choice = 0;
	
	cout << "Please choose an option: \n";
	
	while (true)
	{
		cout << "1. Add an entry\n";
		cout << "2. Report\n";
		cout << "3. Clear\n";
		cout << "4. Exit\n";

		do
		{
			cout << "Enter your choice: ";
			cin >> choice;

			cin.ignore();

			switch (choice)
			{
				case 1: addEntry(); break;
				case 2: report(); break;
				case 3: clear(); break;
				case 4: return;
			}

		} while (choice < 1 || choice > 4);
	}
}