#include "Circle.h"

Circle::Circle()
{}

Circle::Circle(const char * color, const Point& center, double radius)
	: Shape(color)
{
	setCenter(center);
	setRadius(radius);
}

Circle::Circle(const Point& center, double radius)
{
	setCenter(center);
	setRadius(radius);
}

Circle::Circle(const Circle& rhs)
	: Shape(rhs)
{
	copy(rhs);
}

Circle& Circle::operator=(const Circle& rhs)
{
	if (this != &rhs)
	{
		setColor(rhs.color);
		copy(rhs);
	}

	return *this;
}

void Circle::setCenter(const Point& center)
{
	this->center = center;
}

void Circle::setRadius(double radius)
{
	this->radius = radius;
}

void Circle::writeToFile(std::ostream& out) const
{
	out << "<circle cx=\"" << center.getX() 
		<< "\" cy=\"" << center.getY() 
		<< "\" r=\"" << radius 
		<< "\" fill=\"" 
		<< color << "\" />\n";
}

void Circle::print() const
{
	std::cout << "circle " << center << " " << radius << " " << color << "\n";
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::translate(const Point& vec)
{
	center.translate(vec);
}

bool Circle::within(const Point& center, double radius) const
{
	if (!this->center.isInsideCircle(center, radius))
	{
		return false;
	}
	else
	{
		return dist(center, this->center) > (radius - this->radius);
	}
}

bool Circle::within(const Point& bottomLeft, double width, double height) const
{
	if (!center.isInsideRectangle(bottomLeft, width, height))
	{
		return false;
	}
	else
	{
		return ((center.getX() - bottomLeft.getX()) > radius) &&
     			((bottomLeft.getX() + width - center.getX()) > radius) &&
				((center.getY() - bottomLeft.getY()) > radius) &&
				((bottomLeft.getY() + height - center.getY()) > radius);
	}
}

void Circle::copy(const Circle& rhs)
{
	setCenter(rhs.center);
	setRadius(rhs.radius);
}