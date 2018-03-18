#include "Rectangle.h"

Rectangle::Rectangle()
{}

Rectangle::Rectangle(const char * color, const Point& bottomLeft, double width, double height)
	: Shape(color)
{
	setBottomLeft(bottomLeft);
	setWidth(width);
	setHeight(height);
}

Rectangle::Rectangle(const Point& bottomLeft, double width, double height)
{
	setBottomLeft(bottomLeft);
	setWidth(width);
	setHeight(height);
}

Rectangle::Rectangle(const Rectangle& rhs)
	: Shape(rhs)
{
	copy(rhs);
}

Rectangle& Rectangle::operator=(const Rectangle& rhs)
{
	if (this != &rhs)
	{
		setColor(rhs.color);
		copy(rhs);
	}

	return *this;
}

void Rectangle::setBottomLeft(const Point& bottomLeft)
{
	this->bottomLeft = bottomLeft;
}

void Rectangle::setWidth(double width)
{
	this->width = width;
}

void Rectangle::setHeight(double height)
{
	this->height = height;
}

void Rectangle::writeToFile(std::ostream& out) const
{
	out << "<rect x=\"" << bottomLeft.getX() 
		<< "\" y=\"" << bottomLeft.getY() 
		<< "\" width=\"" << width 
		<< "\" height=\"" << height
		<< "\" fill=\"" << color
		<< "\" />\n";
}

void Rectangle::print() const
{
	std::cout << "rectangle " << bottomLeft << " " << width << " " << height << " " << color << "\n";
}

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

void Rectangle::translate(const Point& vec)
{
	bottomLeft.translate(vec);
}

bool Rectangle::within(const Point& center, double radius) const
{
	Point b, c, d;
	findPoints(b, c, d);
	
	return bottomLeft.isInsideCircle(center, radius) &&
		   b.isInsideCircle(center, radius) &&
    	   c.isInsideCircle(center, radius) &&
           d.isInsideCircle(center, radius);
}

bool Rectangle::within(const Point& bottomLeft, double width, double height) const
{
	Point b, c, d;
	findPoints(b, c, d);
	
	return this->bottomLeft.isInsideRectangle(bottomLeft, width, height) &&
		   b.isInsideRectangle(bottomLeft, width, height) &&
		   c.isInsideRectangle(bottomLeft, width, height) &&
		   d.isInsideRectangle(bottomLeft, width, height);
}

void Rectangle::findPoints(Point& BR, Point& UL, Point& UR) const
{
	BR.setX(bottomLeft.getX() + width);
	BR.setY(bottomLeft.getY());

	UL.setX(bottomLeft.getX());
	UL.setY(bottomLeft.getY() + height);

	UR.setX(bottomLeft.getX() + width);
	UR.setY(bottomLeft.getY() + height);
}

void Rectangle::copy(const Rectangle& rhs)
{
	setBottomLeft(rhs.bottomLeft);
	setWidth(rhs.width);
	setHeight(rhs.height);
}