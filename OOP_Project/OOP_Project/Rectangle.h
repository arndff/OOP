#ifndef _RECTANGLE_HEADER_INCLUDED_
#define _RECTANGLE_HEADER_INCLUDED_

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(const char *, const Point&, double, double);
	Rectangle(const Point&, double, double);
	Rectangle(const Rectangle&);
	Rectangle& operator=(const Rectangle&);

	void setBottomLeft(const Point&);
	void setWidth(double);
	void setHeight(double);

	Point getBottomLeft() const { return bottomLeft; }
	double getWidth() const { return width; }
	double getHeight() const { return height; }

public:
	virtual void writeToFile(std::ostream&) const;
	virtual void print() const;
	virtual Shape* clone() const;
	virtual void translate(const Point&);
	virtual bool within(const Point&, double) const;
	virtual bool within(const Point&, double, double) const;

	virtual const char * getName() const { return "rectangle"; }

private:
	void findPoints(Point&, Point&, Point&) const;

	void copy(const Rectangle&);

private:
	Point bottomLeft;
	double width;
	double height;
};

#endif // !_RECTANGLE_HEADER_INCLUDED_