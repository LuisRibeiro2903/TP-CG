#include "engine/frustum/plane.hpp"

void Plane::setNormalAndPoint(Point &normal, Point &point)
{
    _normal = normal;
    _A = normal.x();
    _B = normal.y();
    _C = normal.z();
    _D = -(_A * point.x() + _B * point.y() + _C * point.z());
}

float Plane::signedDistance(Point &p)
{
    return _A * p.x() + _B * p.y() + _C * p.z() + _D;
}