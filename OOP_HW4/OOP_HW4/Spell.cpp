#include <iostream>
#include <cassert>
#include "Spell.h"

Spell::Spell()
	: label(nullptr)
	, type(TYPE_UNKNOWN)
{}

Spell::Spell(const char * _label, Type _type, size_t _mana)
	: label(nullptr)
{
	setLabel(_label);
	setType(_type);
	setMana(_mana);
}

Spell::Spell(const Spell& rhs)
	: label(nullptr)
	, type(TYPE_UNKNOWN)
{
	copy(rhs);
}

Spell& Spell::operator=(const Spell& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

Spell::~Spell()
{
	destroy();
}

void Spell::setLabel(const char * _label)
{	
	label = new char[strlen(_label) + 1];
	strcpy(label, _label);
}

void Spell::setType(Type _type)
{
	if (_type <= TYPE_UNKNOWN || _type >= TYPE_COUNT)
	{
		std::cout 
			<< "Invalid type. It must be a number between " << TYPE_UNKNOWN << " and " << TYPE_COUNT << std::endl;
		
		return;
	}

	type = _type;
}

void Spell::setMana(size_t _mana) { assert(_mana > 0); mana = _mana; }

const char * Spell::getType() const
{
	switch (type)
	{
		case POLYMORPH: return "Polymorph";
		case MUTATE: return "Mutate";
		case SHADOW: return "Shadow";
		default: return nullptr;
	}
}

void Spell::printSpell() const
{
	std::cout << getLabel() << " " << getType() << " " << getMana() << std::endl;
}

void Spell::copy(const Spell& rhs)
{
	setLabel(rhs.label);
	setType(rhs.type);
	setMana(rhs.mana);
}

void Spell::destroy()
{
	delete[] label;
	label = nullptr;
}

bool operator==(const Spell& s1, const Spell& s2)
{
	return (strcmp(s1.getLabel(), s2.getLabel()) == 0 && 
		    s1.getType() == s2.getType() && 
		    s1.getMana() == s2.getMana());
}

bool operator!=(const Spell& s1, const Spell& s2) 
{ 
	return !(s1 == s2); 
}