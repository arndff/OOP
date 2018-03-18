#include "Point.h"

Point::Point()
{}

Point::Point(double x, double y)
{
	setX(x);
	setY(y);
}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}

std::ostream& operator << (std::ostream& os, const Point& p)
{
	os << p.getX() << " " << p.getY();
	return os;
}

void Point::translate(const Point& vec)
{
	x += vec.x;
	y += vec.y;
}

bool Point::isInsideCircle(const Point& center, double radius) const
{
	return (x - center.x)*(x - center.x) + (y - center.y)*(y - center.y) < radius*radius;
}

bool Point::isInsideRectangle(const Point& bottomLeft, double width, double height) const
{
	bool dx = x > bottomLeft.x && x < (bottomLeft.x + width);
	bool dy = y > bottomLeft.y && y < (bottomLeft.y + height);

	return dx && dy;
}

double dist(const Point& a, const Point& b)
{
	return sqrt( (a.getX() - b.getX()) * (a.getX() - b.getX()) +
		         (a.getY() - b.getY()) * (a.getY() - b.getY()) );
}