#ifndef _COMMANDER_HEADER_
#define _COMMANDER_HEADER_

#include "Soldier.h"
#include "Warlock.h"

class Commander : public Soldier
{
public:
	Commander();
	Commander(const char *, size_t, size_t, size_t, const char *, const Warlock *, size_t);
	Commander(const Commander&);
	Commander& operator=(const Commander&);
	~Commander();

public:
	void setArmyName(const char *);
	
	char * getArmyName() const { return armyName; }
	size_t getArmyLevel() const;
	double getAvgArmyLevel() const;
	size_t getArmySize() const;

	size_t getArmyMana() const;
	double getAvgArmyMana() const;

	size_t getArmySalary() const;

public:
	Warlock operator[](int) const;
	Warlock& operator[](int);

private:
	void copyWarlocks(const Warlock*, size_t);

	void copy(const Commander&);
	void destroy();

private:
	char * armyName;
	Warlock * warlocks;
	size_t warlocksCnt;
};

#endif // !_COMMANDER_HEADER_