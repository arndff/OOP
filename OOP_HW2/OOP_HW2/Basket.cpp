#include <iostream>
#include <fstream>
#include <cassert>
#include "Basket.h"

using namespace std;

Basket::Basket()
	: owner(nullptr)
	, arr(nullptr)
	, size(INITIAL_SIZE)
	, capacity(INITIAL_CAPACITY)
{
	arr = new Egg[capacity];
}

Basket::Basket(const char * _owner)
	: size(INITIAL_SIZE)
	, capacity(INITIAL_CAPACITY)
{
	setOwner(_owner);

	arr = new Egg[capacity];
}

Basket::Basket(const Basket& rhs)
	: owner(nullptr)
	, arr(nullptr)
{
	copy(rhs);
}

Basket& Basket::operator=(const Basket& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

Basket::~Basket()
{
	destroy();
}

void Basket::add(const Egg& e)
{
	assert(e.getName());

	if (!containsEgg(e.getName()))
	{
		if (size == capacity)
		{
			resize(2*size);
		}

		arr[size++] = e;
	}
	else
	{
		cout << "There's already an egg with that name.\n";
	}
}

void Basket::del(const char * eggName)
{
	assert(eggName);

	if (containsEgg(eggName))
	{
		Egg * tmp = new Egg[capacity - 1];
		size_t tmpCnt = 0;
		
		for (size_t i = 0; i < size; ++i)
		{
			if (!(strcmp(arr[i].getName(), eggName) == 0))
			{
				tmp[tmpCnt++] = arr[i];
			}
		}

		delete[] arr;
		arr = tmp;
		--size;
		
		if (size + 1 == capacity / 2)
		{
			resize(capacity / 2);
		}
	}
	else
	{
		cout << "Your basket doesn't contain an egg with that name.\n";
	}
}

void Basket::serialize() const
{
	char* fileName = generateFileName();

	ofstream out(fileName, ios::binary | ios::trunc);
	if (!out) 
	{ 
		cout << "Problem with the file...\n"; 
		return; 
	}

	size_t len = strlen(owner);
	out.write((const char *)&len, sizeof(len));
	out.write(owner, len);
	out.write((const char *)&size, sizeof(size));
	out.write((const char*)&capacity, sizeof(capacity));

	for (size_t i = 0; i < size; ++i)
	{
		arr[i].serialize(out);
	}

	delete[] fileName;
	out.clear();
	out.close();
}

void Basket::deserialize()
{
	char* fileName = generateFileName();

	ifstream in(fileName, ios::binary);
	if (!in) 
	{ 
		cout << "Problem with the file...\n"; 
		return; 
	}

	Basket b;
	size_t len = 0;
	in.read((char*)&len, sizeof(len));
	b.owner = new char[len + 1];
	in.read(b.owner, len);
	b.owner[len] = '\0';
	in.read((char*)&b.size, sizeof(b.size));
	in.read((char*)&b.capacity, sizeof(b.capacity));
	b.arr = new Egg[b.capacity];

	for (size_t i = 0; i < b.size; ++i)
	{
		b.arr[i].deserialize(in);
	}

	in.close();
	*this = b;
}

//report_nameOfBasket.txt
void Basket::report() const
{
	char * fname = generateReportName();
	
	ofstream out(fname, ios::trunc);
	writeEggsToFile(out);
	
	delete[] fname;
	out.close();
}

void Basket::setOwner(const char * _owner)
{
	if (!_owner)
	{
		cout << "Not a valid owner name.\n";
		return;
	}

	owner = new char[strlen(_owner) + 1];
	strcpy(owner, _owner);
}

void Basket::writeEggsToFile(ofstream& out) const
{
	for (size_t i = 0; i < size; ++i)
	{
		out << "egg " << i + 1 << ": " << arr[i].getName() << ", " << arr[i].getSize() << "\n";
	}
}

//OPERATORS:

Egg& Basket::operator[](int idx)
{
	return arr[idx];
}

Egg Basket::operator[](int idx) const
{
	return arr[idx];
}

Egg& Basket::operator[](const char * eggName)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (strcmp(arr[i].getName(), eggName) == 0)
		{
			return arr[i];
		}
	}

	throw runtime_error("There's no object with that name.\n");
}

Egg Basket::operator[](const char * eggName) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (strcmp(arr[i].getName(), eggName) == 0)
		{
			return arr[i];
		}
	}

	throw runtime_error("There's no object with that name.\n");
}

Basket& Basket::operator+=(const Basket& rhs)
{
	char * tmpName = generateName(owner, rhs.owner, "_and_");
	delete[] owner;
	owner = tmpName;

	Egg * tmpArr = new Egg[capacity+rhs.capacity];
	size_t tmpCnt = 0;

	for (size_t i = 0; i < this->size; ++i)
	{
		tmpArr[tmpCnt++] = this->arr[i];
	}
	for (size_t i = 0; i < rhs.size; ++i)
	{
		tmpArr[tmpCnt++] = rhs.arr[i];
	}

	size += rhs.size;
	capacity += rhs.capacity;
	delete[] arr;
	arr = tmpArr;

	return *this;
}

Basket& Basket::operator+=(const char * str)
{
	for (size_t i = 0; i < size; ++i)
	{
		char * tmp;
		tmp = new char[strlen(arr[i].getName()) + strlen(str) + 1];
		
		strcpy(tmp, arr[i].getName());
		strcat(tmp, str);
		arr[i].setName(tmp);
		
		delete[] tmp;
	}

	return *this;
}

Basket& Basket::operator*=(size_t eggSize)
{
	for (size_t i = 0; i < size; ++i)
	{
		arr[i].setSize(arr[i].getSize()*eggSize);
	}

	return *this;
}

Basket& Basket::operator/=(size_t eggSize)
{
	if (eggSize == 0)
	{
		throw logic_error("Can't divide by zero.\n");
	}

	for (size_t i = 0; i < size; ++i)
	{
		arr[i].setSize(arr[i].getSize() / eggSize);
	}

	return *this;
}

Basket& Basket::operator%=(const Basket& rhs)
{
	char * tmpName = generateName(owner, rhs.owner, "_X_");

	delete[] owner;
	owner = tmpName;

	size_t tmpSize = 0, tmpCapacity = 2;
	Egg * tmpArr = new Egg[tmpCapacity];

	for (size_t i = 0; i < size; ++i)
	{
		if (rhs.containsEgg(arr[i].getName()))
		{
			if (tmpSize == tmpCapacity)
			{
				resize(tmpSize * 2);
			}

			tmpArr[tmpSize++] = arr[i];
		}
	}

	size = tmpSize;
	capacity = tmpCapacity;
	delete[] arr;
	arr = tmpArr;

	return *this;
}


Basket operator+(const Basket& b1, const Basket& b2)
{
	Basket res(b1);
	res += b2;
	return res;
}

Basket operator+(const Basket& b, const char * str)
{
	Basket res(b);
	res += str;
	return res;
}

Basket operator*(const Basket& b, size_t eggSize)
{
	Basket res(b);
	res *= eggSize;
	return res;
}

Basket operator/(const Basket& b, size_t eggSize)
{
	if (eggSize == 0)
	{
		throw logic_error("Can't divide by zero.\n");
	}

	Basket res(b);
	res /= eggSize;
	return res;
}

Basket operator%(const Basket& b1, const Basket& b2)
{
	Basket res(b1);
	res %= b2;
	return res;
}


bool operator==(const Basket& b1, const Basket& b2)
{
	if (b1.getSize() != b2.getSize())
	{
		return false;
	}

	size_t sz = b1.getSize();

	for (size_t i = 0; i < sz; ++i)
	{
		if (b1[i] != b2[i])
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const Basket& b1, const Basket& b2)
{
	return !(b1 == b2);
}

bool operator<(const Basket& b1, const Basket& b2)
{
	size_t sz1 = b1.getSize(), 
		   sz2 = b2.getSize();
	
	for (size_t i = 0, j = 0; i < sz1 && j < sz2; ++i, ++j)
	{
		if (!(strcmp(b1[i].getName(), b2[i].getName()) < 0))
		{
			return false;
		}
	}

	return true;
}

bool operator<=(const Basket& b1, const Basket& b2)
{
	return (b1 < b2 || b1 == b2);
}

bool operator>=(const Basket& b1, const Basket& b2)
{
	return (!(b1 < b2) || b1 == b2);
}

//helper function for add/del
bool Basket::containsEgg(const char* eggName) const
{
	for(size_t i = 0; i < size; ++i)
	{
		if (strcmp(arr[i].getName(), eggName) == 0)
		{
			return true;
		}
	}

	return false;
}

char* Basket::generateFileName() const
{
	char extension[] = ".dat";
	char* fileName = new char[strlen(owner) + strlen(extension) + 1];
	strcpy(fileName, owner);
	strcat(fileName, extension);

	return fileName;
}

char* Basket::generateReportName() const
{
	char* fname;
	const char * s1 = "report_";
	const char * s2 = ".txt";
	fname = new char[strlen(s1) + strlen(owner) + strlen(s2) + 1];

	strcpy(fname, s1);
	strcat(fname, owner);
	strcat(fname, s2);

	return fname;
}

char * Basket::generateName(const char * o1, const char * o2, const char * mid) const
{
	char * res = new char[strlen(o1) + strlen(mid) + strlen(o2) + 1];

	strcpy(res, o1);
	strcat(res, mid);
	strcat(res, o2);

	return res;
}

//private functions
void Basket::copy(const Basket& rhs)
{
	owner = new char[strlen(rhs.owner) + 1];
	strcpy(owner, rhs.owner);

	arr = new Egg[rhs.size];

	for (size_t i = 0; i <rhs.size; ++i)
	{
		arr[i] = rhs.arr[i];
	}

	size = rhs.size;
	capacity = rhs.capacity;
}

void Basket::destroy()
{
	delete[] owner;
	delete[] arr;

	owner = nullptr;
	arr = nullptr;
}

void Basket::resize(size_t newCapacity)
{
	Egg * temp = new Egg[newCapacity];

	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = temp;
	capacity = newCapacity;
}
