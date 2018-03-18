#include <iostream>
#include <cassert>
#include "MagicBook.h"

MagicBook::MagicBook(Spell * _pages, size_t _pagesCnt)
	: pages(nullptr)
{
	setPages(_pages, _pagesCnt);
}

MagicBook::MagicBook(const MagicBook& rhs)
	: pages(nullptr)
{
	copy(rhs);
}

MagicBook& MagicBook::operator=(const MagicBook& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

MagicBook::~MagicBook()
{
	destroy();
}

void MagicBook::setPages(const Spell* pages, size_t pagesCnt)
{
	this->pages = new Spell[pagesCnt];

	for (size_t i = 0; i < pagesCnt; ++i)
	{
		this->pages[i] = pages[i];
	}

	this->pagesCnt = pagesCnt + 1;
}

void MagicBook::print() const
{
	for (size_t i = 0; i < pagesCnt - 1; ++i)
	{
		pages[i].printSpell();
	}
}

Spell& MagicBook::operator[](int idx)
{
	return pages[idx];
}

Spell MagicBook::operator[](int idx) const
{
	return pages[idx];
}

void MagicBook::resizeMagicBook(const Spell& s)
{
	Spell * tmp = new Spell[getPagesCnt() - 1];
	size_t tmpCnt = 0;

	for (size_t i = 0; i < getPagesCnt() - 1; ++i)
	{
		if (pages[i] != s)
		{
			tmp[tmpCnt++] = s;
		}
	}

	setPages(tmp, tmpCnt);

	delete[] tmp;
}

void MagicBook::copy(const MagicBook& rhs)
{
	setPages(rhs.pages, rhs.pagesCnt-1);
}

void MagicBook::destroy()
{
	delete[] pages;
	pages = nullptr;
}