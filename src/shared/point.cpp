#include "point.hpp"

Point::Point(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

float Point::x() const
{
    return _x;
}

float Point::y() const
{
    return _y;
}

float Point::z() const
{
    return _z;
}

void Point::setX(float x)
{
    _x = x;
}

void Point::setY(float y)
{
    _y = y;
}

void Point::setZ(float z)
{
    _z = z;
}

