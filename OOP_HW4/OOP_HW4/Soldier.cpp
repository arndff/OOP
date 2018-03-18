#include <iostream>
#include <cassert>
#include "Soldier.h"

Soldier::Soldier()
	: name(nullptr)
{}

Soldier::Soldier(const char * _name, size_t _age, size_t _level, size_t _salary)
	: name(nullptr)
	, age(_age)
	, level(_level)
	, salary(_salary)
{
	setName(_name);
}

Soldier::Soldier(const Soldier& rhs)
	: name(nullptr)
{
	copy(rhs);
}

Soldier& Soldier::operator=(const Soldier &rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

Soldier::~Soldier()
{
        //std::cout << "Soldier's dtor is called!\n";
	destroy();
}

void Soldier::setName(const char * name)
{
	if (!name)
	{
		return;
	}
	
	delete[] this->name;
	this->name = setNameHelper(name);
}

void Soldier::setAge(size_t age) 
{ 
	assert(age > 0); 
	this->age = age; 
}

void Soldier::setLevel(size_t level)
{
	assert(level > 0); 
	this->level = level; 
}

void Soldier::setSalary(size_t salary) 
{ 
	assert(salary > 0); 
	this->salary = salary; 
}

char * Soldier::setNameHelper(const char* name)
{
	char * res = new char[strlen(name) + 1];
	strcpy(res, name);
	
	return res;
}

void Soldier::copy(const Soldier& rhs)
{
	setName(rhs.name);
	setAge(rhs.age);
	setLevel(rhs.level);
	setSalary(rhs.salary);
}

void Soldier::destroy()
{
	delete[] name;
	name = nullptr;
}
