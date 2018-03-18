#ifndef _SHAPE_HEADER_INCLUDED_
#define _SHAPE_HEADER_INCLUDED_

#include "Point.h"

class Shape
{
public:
	Shape();
	Shape(const char *);
	Shape(const Shape&);
	Shape& operator=(const Shape&);
	virtual ~Shape() { delete[] color; }

public:
	virtual void writeToFile(std::ostream&) const = 0;
	virtual void print() const = 0;
	virtual Shape* clone() const = 0;
	virtual void translate(const Point&) = 0;
	virtual bool within(const Point&, double) const = 0;
	virtual bool within(const Point&, double, double) const = 0;

public:
	void setColor(const char *);
	const char * getColor() const { return color; }

	virtual const char * getName() const = 0;

protected:
	char * color;
};

#endif // !_SHAPE_HEADER_INCLUDED_