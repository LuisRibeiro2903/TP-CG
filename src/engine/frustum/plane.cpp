#include "engine/frustum/plane.hpp"
#include "cgmath.hpp"

void Plane::setNormalAndPoint(Point &normal, Point &point)
{
    _normal.copy(normal);
    _normal.normalize();
    d = -(_normal.innerProduct(point));
}

void Plane::set3Points(Point &v1, Point &v2, Point &v3)
{
    Point aux1, aux2;

    aux1 = v1 - v2;
    aux2 = v3 - v2;

    cross(aux2, aux1, _normal);

    _normal.normalize();
    _point.copy(v2);
    d = -(_normal.innerProduct(_point));
}

float Plane::signedDistance(Point &p)
{
    return (d + _normal.innerProduct(p));
}