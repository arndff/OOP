#ifndef _EGG_HEADER_INCLUDED_
#define _EGG_HEADER_INCLUDED_

#include <fstream>

class Egg
{
public:
	Egg();
	Egg(const char *, size_t);
	Egg(const Egg&);
	Egg& operator=(const Egg&);
	~Egg();

public:
	void setName(const char *);
	void setSize(size_t);
	const char * getName() const { return name; }
	int getSize() const { return size; }

public:
	void serialize(std::ofstream&) const;
	void deserialize(std::ifstream&);

private:
	void copy(const Egg&);
	void destroy();

private:
	char * name;
	size_t size;
};

bool operator==(const Egg&, const Egg&);
bool operator!=(const Egg&, const Egg&);

#endif // _EGG_HEADER_INCLUDED_