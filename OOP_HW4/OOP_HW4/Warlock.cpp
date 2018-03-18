#include <iostream>
#include <cassert>
#include "Warlock.h"

Warlock::Warlock()
	: batallionName(nullptr)
	, batallion(nullptr)
{}

Warlock::Warlock(const char * name, size_t age, size_t level, size_t salary,
	             const char * _batallionName, const Sergeant * _batallion, size_t _sergeantsCnt, size_t _mana, const MagicBook& _book)
	: Soldier(name, age, level, salary)
	, batallionName(nullptr)
	, batallion(nullptr)
	, mana(_mana)
	, book(_book)
{
	setBatallionName(_batallionName);
	copySergeants(_batallion, _sergeantsCnt);
}

Warlock::Warlock(const Warlock& rhs)
	: Soldier(rhs)
	, batallionName(nullptr)
	, batallion(nullptr)
{
	copy(rhs);
}

Warlock& Warlock::operator=(const Warlock& rhs)
{
	if (this != &rhs)
	{
		destroy();
		Soldier::operator=(rhs);
		copy(rhs);
	}

	return *this;
}

Warlock::~Warlock()
{
	destroy();
}

void Warlock::setBatallionName(const char * name)
{
	batallionName = Soldier::setNameHelper(name);
}

void Warlock::setMana(size_t mana) 
{ 
	assert(mana > 0); 
	this->mana = mana; 
}

size_t Warlock::getBatallionLevel() const
{
	size_t totalLevel = 0;
	
	for (size_t i = 0; i < sergeantsCnt; ++i)
	{
		totalLevel += batallion[i].getLevel() + batallion[i].getPlatoonLevel();
	}

	return totalLevel;
}

double Warlock::getAvgBatallionLevel() const
{
	return (double) getBatallionLevel() / sergeantsCnt;
}

size_t Warlock::getBatallionSize() const
{
	size_t batallionSize = 0;

	for (size_t i = 0; i < sergeantsCnt; ++i)
	{
		batallionSize += batallion[i].getSoldiersCnt();
	}

	return batallionSize + sergeantsCnt;
}

size_t Warlock::getBatallionSalary() const
{
	size_t batallionSalary = 0;
	
	for (size_t i = 0; i < sergeantsCnt; ++i)
	{
		batallionSalary += batallion[i].getSalary() + batallion[i].getPlatoonSalary();
	}

	return batallionSalary;
}

void Warlock::useSpell(const Spell& s)
{
	if (mana < s.getMana())
	{
		std::cout << getName() << " doesn't have enough mana to use " << s.getLabel() << " spell.\n";
		return;
	}

	book.resizeMagicBook(s);
	mana -= s.getMana();
}

void Warlock::copySergeants(const Sergeant * batallion, size_t sergeantsCnt)
{
	delete[] this->batallion;
	this->batallion = nullptr;

	Sergeant * tmp = new Sergeant[sergeantsCnt];

	size_t tmpCnt = 0;

	for (size_t i = 0; i < sergeantsCnt; ++i)
	{
		if (this->level > batallion[i].getLevel())
			tmp[tmpCnt++] = batallion[i];
	}

	this->batallion = tmp;
	this->sergeantsCnt = tmpCnt;
}

void Warlock::copy(const Warlock& rhs)
{
	batallionName = Soldier::setNameHelper(rhs.batallionName);
	copySergeants(rhs.batallion, rhs.sergeantsCnt);
	setMana(rhs.mana);
	book = rhs.book;
}

void Warlock::destroy()
{
	delete[] batallionName;
	delete[] batallion;

	batallionName = nullptr;
	batallion = nullptr;
}