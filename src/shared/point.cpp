#include "point.hpp"

Point::Point()
{
    _x = 0;
    _y = 0;
    _z = 0;
}

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

