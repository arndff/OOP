#include "Shape.h"

Shape::Shape()
	: color(nullptr)
{}

Shape::Shape(const char * color)
	: color(nullptr)
{
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

Shape::Shape(const Shape& rhs)
	: color(nullptr)
{
	setColor(rhs.color);
}

Shape& Shape::operator=(const Shape& rhs)
{
	if (this != &rhs)
	{
		setColor(rhs.color);
	}

	return *this;
}

void Shape::setColor(const char * color)
{
	delete[] this->color;
	this->color = nullptr;

	if (!color)
	{
		throw std::runtime_error("Invalid color has been passed.\n");
	}
	else
	{
		this->color = new char[strlen(color) + 1];
		strcpy(this->color, color);
	}
}