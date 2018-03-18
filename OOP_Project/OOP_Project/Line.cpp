#include "Line.h"

Line::Line()
{}

Line::Line(const char * color, const Point& a, const Point& b)
	: Shape(color)
{
	setA(a);
	setB(b);
}

Line::Line(const Line& rhs)
	: Shape(rhs)
{
	copy(rhs);
}

Line& Line::operator=(const Line& rhs)
{
	if (this != &rhs)
	{
		setColor(rhs.color);
		copy(rhs);
	}

	return *this;
}

void Line::setA(const Point& a)
{
	this->a = a;
}

void Line::setB(const Point& b)
{
	this->b = b;
}

void Line::writeToFile(std::ostream& out) const
{
	out << "<line x1=\"" << a.getX()
		<< "\" x2=\"" << a.getY()
		<< "\" y1=\"" << b.getX()
		<< "\" y2=\"" << b.getY()
		<< "\" stroke=\"" << color
		<< "\" />\n";
}

void Line::print() const
{
	std::cout << "line " << a << " " << b << " " << color << "\n";
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::translate(const Point& vec)
{
	a.translate(vec);
	b.translate(vec);
}

bool Line::within(const Point& center, double radius) const
{
	return a.isInsideCircle(center, radius) && b.isInsideCircle(center, radius);
}

bool Line::within(const Point& bottomLeft, double width, double height) const
{	
	return a.isInsideRectangle(bottomLeft, width, height) && b.isInsideRectangle(bottomLeft, width, height);
}

void Line::copy(const Line& rhs)
{
	setA(rhs.a);
	setB(rhs.b);
}