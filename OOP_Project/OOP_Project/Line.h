#ifndef _LINE_HEADER_INCLUDED_
#define _LINE_HEADER_INCLUDED_

#include "Shape.h"

class Line : public Shape
{
public:
	Line();
	Line(const char *, const Point&, const Point&);
	Line(const Line&);
	Line& operator=(const Line&);

	void setA(const Point&);
	void setB(const Point&);

	Point getA() const { return a; }
	Point getB() const { return b; }

public:
	virtual void writeToFile(std::ostream&) const;
	virtual void print() const;
	virtual Shape* clone() const;
	virtual void translate(const Point&);
	virtual bool within(const Point&, double) const;
	virtual bool within(const Point&, double, double) const;

	virtual const char * getName() const { return "line"; }

private:
	void copy(const Line&);

private:
	Point a;
	Point b;
};

#endif // !_LINE_HEADER_INCLUDED_