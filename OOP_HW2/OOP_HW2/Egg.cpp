#include <iostream>

#include <cstring>
#include "Egg.h"

using namespace std;

Egg::Egg()
	: name(nullptr)
{}

Egg::Egg(const char * _name, size_t _size)
	: name(nullptr)
{
	setName(_name);
	setSize(_size);
}

Egg::Egg(const Egg& rhs)
	: name(nullptr)
{
	copy(rhs);
}

Egg& Egg::operator=(const Egg& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

Egg::~Egg()
{
	destroy();
}

void Egg::serialize(std::ofstream& out) const
{
	if (!out)
	{
		cout << "Problem with the file...\n";
		return;
	}

	size_t len = strlen(getName());
	
	out.write((const char *)&len, sizeof(len));
	out.write(name, len);
	out.write((const char *)&size, sizeof(size));
}

void Egg::deserialize(std::ifstream& in)
{
	if (!in)
	{
		cout << "Problem with the file...\n";
		return;
	}

	Egg e;
	size_t len = 0;
	
	in.read((char*)&len, sizeof(len));
	e.name = new char[len + 1];
	in.read(e.name, len);
	e.name[len] = '\0';
	in.read((char *)&e.size, sizeof(e.size));

	*this = e;
}

void Egg::copy(const Egg& rhs)
{
	setName(rhs.name);
	setSize(rhs.size);
}

void Egg::destroy()
{
	delete[] name;
	name = nullptr;
}

void Egg::setName(const char * _name)
{
	if (_name == nullptr) 
	{ 
		throw std::logic_error("Invalid name.\n"); 
	}

	delete[] name;
	//name = nullptr;
	name = strcpy(new char[strlen(_name) + 1], _name);
}

void Egg::setSize(size_t _size)
{
	if (_size <= 0) 
	{ 
		throw std::logic_error("Invalid size.\n"); 
	}

	size = _size;
}

//Operators:
bool operator==(const Egg& e1, const Egg& e2)
{
	return (strcmp(e1.getName(), e2.getName()) == 0);
}

bool operator!=(const Egg& e1, const Egg& e2)
{
	return !(e1 == e2);
}
