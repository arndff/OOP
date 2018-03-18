#include <iostream>
#include "Sergeant.h"

Sergeant::Sergeant()
	: platoonName(nullptr)
	, platoon(nullptr)
{}

Sergeant::Sergeant(const char * name, size_t age, size_t level, size_t salary, 
	               const char * _platoonName, const Soldier * _platoon, size_t _soldiersCnt)
	: Soldier(name, age, level, salary)
	, platoonName(nullptr)
	, platoon(nullptr)
{
	platoonName = Soldier::setNameHelper(_platoonName);
	copySoldiers(_platoon, _soldiersCnt);
}

Sergeant::Sergeant(const Sergeant& rhs)
	: Soldier(rhs)
	, platoonName(nullptr)
	, platoon(nullptr)
{
	copy(rhs);
}

Sergeant& Sergeant::operator=(const Sergeant& rhs)
{
	if (this != &rhs)
	{
		destroy();
		Soldier::operator=(rhs);
		copy(rhs);
	}

	return *this;
}

Sergeant::~Sergeant()
{
	//std::cout << "Sergeant's dtor is called!\n";
	destroy();
}

void Sergeant::setPlatoonName(const char * name)
{
	platoonName = Soldier::setNameHelper(name);
}

size_t Sergeant::getPlatoonLevel() const
{
	size_t totalLevel = 0;
	for (size_t i = 0; i < soldiersCnt; ++i)
	{
		totalLevel += platoon[i].getLevel();
	}

	return totalLevel;
}

double Sergeant::getAvgPlatoonLevel() const
{
	return (double)getPlatoonLevel() / soldiersCnt;
}

size_t Sergeant::getPlatoonSalary() const
{
	size_t platoonSalary = 0;
	for (size_t i = 0; i < soldiersCnt; ++i)
	{
		platoonSalary += platoon[i].getSalary();
	}

	return platoonSalary;
}

void Sergeant::copySoldiers(const Soldier* platoon, size_t soldiersCnt)
{
	delete[] this->platoon;
	this->platoon = new Soldier[soldiersCnt];
	this->soldiersCnt = 0;

	for (size_t i = 0; i < soldiersCnt; ++i)
	{
		if (this->level > platoon[i].getLevel())
		{
			this->platoon[this->soldiersCnt++] = platoon[i];
		}
	}
}

void Sergeant::copy(const Sergeant& rhs)
{
	platoonName = Soldier::setNameHelper(rhs.platoonName);
	copySoldiers(rhs.platoon, rhs.soldiersCnt);
}

void Sergeant::destroy()
{
	delete[] platoonName;
	delete[] platoon;

	platoonName = nullptr;
	platoon = nullptr;
}
