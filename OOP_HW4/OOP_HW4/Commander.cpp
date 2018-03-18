#include <iostream>
#include <cassert>
#include "Commander.h"

Commander::Commander()
	: armyName(nullptr)
	, warlocks(nullptr)
{}

Commander::Commander(const char * name, size_t age, size_t level, size_t salary,
			         const char * _armyName, const Warlock * _warlocks, size_t _warlocksCnt)
	: Soldier(name, age, level, salary)
	, armyName(nullptr)
	, warlocks(nullptr)
{
	setArmyName(_armyName);
	copyWarlocks(_warlocks, _warlocksCnt);
}

Commander::Commander(const Commander& rhs)
	: Soldier(rhs)
	, armyName(nullptr)
	, warlocks(nullptr)
{
	copy(rhs);
}

Commander& Commander::operator=(const Commander& rhs)
{
	if (this != &rhs)
	{
		destroy();
		Soldier::operator=(rhs);
		copy(rhs);
	}

	return *this;
}

Commander::~Commander()
{
	destroy();
}

void Commander::setArmyName(const char * name)
{
	armyName = Soldier::setNameHelper(name);
}

size_t Commander::getArmyLevel() const
{
	size_t totalLevel = 0;
	
	for (size_t i = 0; i < warlocksCnt; ++i)
	{
		totalLevel += warlocks[i].getLevel() + warlocks[i].getBatallionLevel();
	}

	return totalLevel + level;
}

double Commander::getAvgArmyLevel() const
{
	return (double)getArmyLevel() / getArmySize();
}

size_t Commander::getArmySize() const
{
	size_t warlocksSize = 0;
	
	for (size_t i = 0; i < warlocksCnt; ++i)
	{
		warlocksSize += warlocks[i].getBatallionSize();
	}

	return warlocksSize + warlocksCnt + 1;
}

size_t Commander::getArmyMana() const
{
	size_t totalMana = 0;
	
	for (size_t i = 0; i < warlocksCnt; ++i)
	{
		totalMana += warlocks[i].getMana();
	}

	return totalMana;
}

double Commander::getAvgArmyMana() const
{
	return (double)getArmyMana() / warlocksCnt;
}

size_t Commander::getArmySalary() const
{
	size_t armySalary = 0;
	
	for (size_t i = 0; i < warlocksCnt; ++i)
	{
		armySalary += warlocks[i].getSalary() + warlocks[i].getBatallionSalary();
	}

	return armySalary + salary;
}

Warlock Commander::operator[](int idx) const
{
	return warlocks[idx];
}

Warlock& Commander::operator[](int idx)
{
	return warlocks[idx];
}

void Commander::copyWarlocks(const Warlock * warlocks, size_t warlocksCnt)
{
	delete[] this->warlocks;
	this->warlocks = nullptr;

	Warlock * tmp = new Warlock[warlocksCnt];
	size_t tmpCnt = 0;

	for (size_t i = 0; i < warlocksCnt; ++i)
	{
		if (this->level > warlocks[i].getLevel())
			tmp[tmpCnt++] = warlocks[i];
	}

	this->warlocks = tmp;
	this->warlocksCnt = tmpCnt;
}

void Commander::copy(const Commander& rhs)
{
	armyName = Soldier::setNameHelper(rhs.armyName);
	copyWarlocks(rhs.warlocks, rhs.warlocksCnt);
}

void Commander::destroy()
{
	delete[] armyName;
	delete[] warlocks;

	armyName = nullptr;
	warlocks = nullptr;
}