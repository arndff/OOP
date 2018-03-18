#ifndef CARS_DB_HEADER_INCLUDED__
#define CARS_DB_HEADER_INCLUDED__

#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

const size_t MAX_LEN = 23;

struct Person
{
	Person()
		: name("")
		, id(-1)
		, reg(-1)
	{}

	Person(const char * _name, int _id, int _reg)
	{
		assert(strlen(_name) < MAX_LEN + 1);

		strcpy(name, _name);
		id = _id;
		reg = _reg;
	}

	char name[MAX_LEN];
	int id;
	int reg;
};

struct Car
{
	char * car;
	int hp;

	Car()
		: car(nullptr)
	{}

	Car(const char * _car, int _hp)
	{
		car = new char[strlen(_car) + 1];
		strcpy(car, _car);
		hp = _hp;
	}

	~Car()
	{
		delete[] car;
	}
};

const Car cars[] = { { "Lambordgini Murcielago", 670 },
		     { "Mercedes-AMG", 503 },
		     { "Pagani Zonda R", 740 },
	             { "Bugatti Veyron", 1020 }
		   };

const size_t CARS_COUNT = sizeof(cars) / sizeof(Car);

int readID();
int readReg();

bool isRegAvailable(int);
bool isFileAvailable();

void savePerson(const char*, int, int);
void addEntry();

int getHp(int);
double avgHp();

const char * getName(int);
int findMax(int*);
const char * mostPopularCar();

void countEntries(size_t&);
void toArray(Person*&);
bool isSaved(const char *, char **, size_t);
void processOwnersHelper(Person*&, char **&, size_t);
void processOwners();

void report();
void clear();

void menu();

#endif // !CARS_DB_HEADER_INCLUDED__
