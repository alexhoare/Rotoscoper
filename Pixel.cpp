#include "Pixel.h"

Pixel::Pixel()
{
	this->color = Point3_<uchar>(0, 0, 0);
}

Pixel::Pixel(Point3_<uchar> color)
{
	this->color = color;
}

Point3_<uchar> Pixel::getColor()
{
	return this->color;
}

void Pixel::setColor(Point3_<uchar> color)
{
	this->color = color;
}
