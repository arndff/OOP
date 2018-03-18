#ifndef _POINT_HEADER_INCLUDED_
#define _POINT_HEADER_INCLUDED_

#include <iostream>

class Point
{
public:
	Point();
	Point(double, double);

	void setX(double);
	void setY(double);

	double getX() const { return x; }
	double getY() const { return y; }

	friend std::ostream& operator<< (std::ostream&, const Point&);

	bool isInsideCircle(const Point&, double) const;
	bool isInsideRectangle(const Point&, double, double) const;
	void translate(const Point&);

private:
	double x;
	double y;
};

//calculates the distances between two points
double dist(const Point&, const Point&);

#endif // !_POINT_HEADER_INCLUDED_