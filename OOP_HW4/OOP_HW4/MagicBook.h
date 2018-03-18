#ifndef _MAGIC_BOOK_HEADER_
#define _MAGIC_BOOK_HEADER_

#include "Spell.h"

class MagicBook
{
public:
	MagicBook()
		: pages(nullptr)
		, pagesCnt(0)
	{}
	MagicBook(Spell*, size_t);
	MagicBook(const MagicBook&);
	MagicBook& operator=(const MagicBook&);
	~MagicBook();

public:
	void setPages(const Spell*, size_t);
	size_t getPagesCnt() { return pagesCnt; }

	void print() const;
	
	Spell& operator[](int);
	Spell operator[](int) const;

	void resizeMagicBook(const Spell&);

private:
	void copy(const MagicBook&);
	void destroy();

private:
	Spell * pages;
	size_t pagesCnt;
};

#endif // !_MAGIC_BOOK_HEADER_