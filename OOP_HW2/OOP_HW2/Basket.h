#ifndef _BASKET_HEADER_INCLUDED_
#define _BASKET_HEADER_INCLUDED_

#include "Egg.h"

class Basket
{
public:
	Basket();
	Basket(const char *);
	Basket(const Basket&);
	Basket& operator=(const Basket&);
	~Basket();

public:
	void add(const Egg&);
	void del(const char *);

public:
	void serialize() const;
	void deserialize();
	void report() const;

public:
	void setOwner(const char *);
	const char * getOwner() const { return owner; }
	size_t getSize() const { return size; }
	size_t getCapacity() const { return capacity; }

//operators
public:
	Egg& operator[](int);
	Egg operator[](int) const;

	Egg& operator[](const char *);
	Egg operator[](const char *) const;

	Basket& operator+=(const Basket&);
	Basket& operator+=(const char *);
	Basket& operator*=(size_t);
	Basket& operator/=(size_t);
	Basket& operator%=(const Basket&);

private:
	bool containsEgg(const char *) const;
	
	char* generateFileName() const;
	char* generateReportName() const;
	char* generateName(const char*, const char*, const char*) const;
	void writeEggsToFile(std::ofstream&) const;

private:
	void copy(const Basket&);
	void destroy();
	void resize(size_t);

private:
	static const size_t INITIAL_SIZE = 0;
	static const size_t INITIAL_CAPACITY = 2;

	char * owner;
	Egg * arr;
	size_t size;
	size_t capacity;
};

Basket operator+(const Basket&, const Basket&);
Basket operator+(const Basket&, const char *);
Basket operator*(const Basket&, size_t);
Basket operator/(const Basket&, size_t);
Basket operator%(const Basket&, const Basket&);

bool operator==(const Basket&, const Basket&);
bool operator!=(const Basket&, const Basket&);
bool operator<(const Basket&, const Basket&);
bool operator<=(const Basket&, const Basket&);
bool operator>=(const Basket&, const Basket&);

#endif // !_BASKET_HEADER_INCLUDED_