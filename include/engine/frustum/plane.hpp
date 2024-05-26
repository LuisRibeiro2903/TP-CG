#ifndef PLANE_HPP
#define PLANE_HPP

#include "point.hpp"

class Plane {
    private:
        Point _normal, _point;
        float d;
    public:
        Plane() {};
        void setNormalAndPoint(Point &normal, Point &point);
        void set3Points(Point &v1, Point &v2, Point &v3);
        float signedDistance(Point &p);
        Point normal() const { return _normal; }
};

#endif