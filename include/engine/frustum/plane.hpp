#ifndef PLANE_HPP
#define PLANE_HPP

#include "point.hpp"

class Plane {
    private:
        float _A, _B, _C, _D;
        Point _normal;
    public:
        Plane() {};
        void setNormalAndPoint(Point &normal, Point &point);
        float signedDistance(Point &p);
        Point normal() const { return _normal; }
};

#endif