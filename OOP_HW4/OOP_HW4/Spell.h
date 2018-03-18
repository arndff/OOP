#ifndef _SPELL_HEADER_
#define _SPELL_HEADER_

enum Type
{
	TYPE_UNKNOWN = -1,
	POLYMORPH,
	MUTATE,
	SHADOW,

	TYPE_COUNT
};

class Spell
{
public:
	Spell();
	Spell(const char *, Type, size_t);
	Spell(const Spell&);
	Spell& operator=(const Spell&);
	~Spell();

public:
	void setLabel(const char *);
	void setType(Type);
	void setMana(size_t);

	const char * getLabel() const { return label; }
	const char * getType() const; 
	size_t getMana() const { return mana; }

	void printSpell() const;

private:
	void copy(const Spell&);
	void destroy();

private:
	char * label;
	Type type;
	size_t mana;
};

bool operator==(const Spell&, const Spell&);
bool operator!=(const Spell&, const Spell&);

#endif // !_SPELL_HEADER_