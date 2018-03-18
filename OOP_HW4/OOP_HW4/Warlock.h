#ifndef _WARLOCK_HEADER_
#define _WARLOCK_HEADER_

#include "Soldier.h"
#include "Sergeant.h"
#include "MagicBook.h"

class Warlock : public Soldier
{
public:
	Warlock();
	Warlock(const char *, size_t, size_t, size_t, const char *, const Sergeant *, size_t, size_t, const MagicBook&);
	Warlock(const Warlock&);
	Warlock& operator=(const Warlock&);
	~Warlock();

public:
	void setBatallionName(const char *);
	void setMana(size_t);

	size_t getBatallionLevel() const;
	double getAvgBatallionLevel() const;
	size_t getBatallionSize() const;
	size_t getMana() const { return mana; }

	size_t getBatallionSalary() const;

	void useSpell(const Spell&);

private:
	void copySergeants(const Sergeant*, size_t);
	
	void copy(const Warlock&);
	void destroy();

private:
	char * batallionName;
	Sergeant * batallion;
	size_t sergeantsCnt;
	size_t mana;
	MagicBook book;
};

#endif // !_WARLOCK_HEADER_