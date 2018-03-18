#include <iostream>
using namespace std;

#include "Soldier.h"
#include "Sergeant.h"
#include "Spell.h"
#include "MagicBook.h"
#include "Warlock.h"
#include "Commander.h"

const size_t armyLevel(const Commander& c) { return c.getArmyLevel(); }

const double armyAvgLevel(const Commander& c) { return c.getAvgArmyLevel(); }

const size_t armyMana(const Commander& c) { return c.getArmyMana(); }

const double armyAvgMana(const Commander& c) { return c.getAvgArmyMana(); }

const size_t armySalary(const Commander& c) { return c.getArmySalary(); }

void test()
{
	Soldier s1[] = { { "Ivan", 22, 2, 3000 },{ "Vlado",21,4,1999 } };
	Sergeant ser1("Stoqn", 24, 7, 5000, "Vzvod1", s1, 2);
	Soldier s2[] = { { "Nikola", 22, 3, 3000 },{ "Sasho",21,5,1999 } };
	Sergeant ser2("Petar", 19, 9, 2020, "Vzvod2", s2, 2);
	Soldier s3[] = { { "Simeon", 22, 1, 3000 },{ "Kamen",21,6,1999 } };
	Sergeant ser3("Dimo", 21, 10, 2222, "Vzvod3", s3, 2);

	Spell spells[] = { { "card1",POLYMORPH,2000 },{ "card2",MUTATE,1500 } };
	MagicBook mb(spells, 2);

	Sergeant ser_arr[] = { ser1,ser2 };
	Sergeant ser_arr2[] = { ser3 };

	Warlock w[] = { { "Viktor",22,15,5000,"Batallion1",ser_arr,2,10000,mb },{ "Todor",22,20,6000,"Batallion2",ser_arr2,1,15000,mb } };

	Commander c("GEORGI", 22, 30, 99999, "BEST_ARMY", w, 2);

	const double res = armyAvgLevel(c);
	cout << res << endl;

	mb.print();
	cout << "---\n";
	cout << w[0].getMana() << endl;
	
	c[0].useSpell(spells[0]);
	
	mb.print();
	
	cout << c[0].getMana();
	cout << "\n---\n";
	
	cout << c.getArmyMana() << endl;
	cout << c.getAvgArmyMana() << endl;
}

void test2()
{
	Soldier s1[] = { { "Ivan", 22, 2, 3000 },{ "Vlado",21,4,1999 } };

	Soldier *s = new Sergeant("Stoqn", 24, 7, 5000, "Vzvod1", s1, 2);

	delete s;
}

int main()
{
	test();
	//test2();

	return 0;
}
