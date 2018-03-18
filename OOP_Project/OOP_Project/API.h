#ifndef _API_HEADER_INCLUDED_
#define _API_HEADER_INCLUDED_

#include "Shape.h"

class API
{
public:
	API();
	~API();

public:
	void setPath(const char *);
	const char * getFileName() const;

public:
	void open(const char *);
	void close();
	void save();
	void saveAs(const char *);

private:
	void readData(std::ifstream&);
	void writeData(std::ofstream&) const;

public:
	void create(const Shape*);
	void erase(size_t);

	void print() const;
	void translate(const Point&);
	void translate(const Point&, size_t);
	void within(const Point&, double) const;
	void within(const Point&, double, double) const;

private:
	void resize(size_t);
	void destroy();
	template <typename T>
	void allocate(T*& dest, size_t size) const
	{
		dest = new T[size];
	}

//parsing file helper functions
private:
	bool isLetter(char) const;
	void goToNextAttr(std::istream&) const;
	void skipTillEnd(std::ifstream&) const;

	bool isSVGOpened(const char[]) const;
	
	char* readString(std::ifstream&) const;
	void extractValue(std::ifstream&, double&) const;
	
	void parseCircle(std::ifstream&);
	void parseRect(std::ifstream&);
	void parseLine(std::ifstream&);

private:
	API(const API&) = delete;
	API& operator=(const API&) = delete;

private:
	static const size_t INITIAL_SIZE = 0;
	static const size_t INITIAL_CAPACITY = 2;

	Shape** data;
	size_t size;
	size_t capacity;
	char * filePath;
};

#endif // !_GROUP_HEADER_INCLUDED_