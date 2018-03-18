#ifndef _CIRCLE_HEADER_INCLUDED_
#define _CIRCLE_HEADER_INCLUDED_

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle();
	Circle(const char * color, const Point&, double);
	Circle(const Point&, double);
	Circle(const Circle&);
	Circle& operator=(const Circle&);

	void setCenter(const Point&);
	void setRadius(double);

	Point getCenter() const { return center; }
	double getRadius() const { return radius; }

public:
	virtual void writeToFile(std::ostream&) const;
	virtual void print() const;
	virtual Shape* clone() const;
	virtual void translate(const Point&);
	virtual bool within(const Point&, double) const;
	virtual bool within(const Point&, double, double) const;

	virtual const char * getName() const { return "circle"; }

private:
	void copy(const Circle&);

private:
	Point center;
	double radius;
};

#endif // !_CIRCLE_HEADER_INCLUDED_