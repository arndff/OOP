#ifndef _SERGEANT_HEADER_
#define _SERGEANT_HEADER_

#include "Soldier.h"

class Sergeant : public Soldier
{
public:
	Sergeant();
	Sergeant(const char *, size_t, size_t, size_t, const char *, const Soldier *, size_t);
	Sergeant(const Sergeant&);
	Sergeant& operator=(const Sergeant&);
	~Sergeant();

public:
	void setPlatoonName(const char *);
	
	double getAvgPlatoonLevel() const;
	size_t getPlatoonLevel() const;
	size_t getSoldiersCnt() const { return soldiersCnt; }

	size_t getPlatoonSalary() const;

private:
	void copySoldiers(const Soldier*, size_t);

	void copy(const Sergeant&);
	void destroy();
	
private:
	char * platoonName;
	Soldier * platoon;
	size_t soldiersCnt;
};

#endif // !_SERGEANT_HEADER_
