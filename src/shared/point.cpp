#include "point.hpp"

Point::Point()
{
    _x = 0;
    _y = 0;
    _z = 0;
}

Point operator+(const Point& other) const {
    return Point(_x + other._x, _y + other._y, _z + other._z);
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

float * Point::data()
{
    return new float[3]{_x, _y, _z};
}
