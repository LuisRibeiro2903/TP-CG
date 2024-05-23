#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

class Point {
    private:
        float _x, _y, _z;
    
    public:

        Point(float x, float y, float z);
        Point();

        float x() const;
        float y() const;
        float z() const;

        void setX(float x);
        void setY(float y);
        void setZ(float z);
        float * data();
        void handleIsNan();
        void normalize();

        Point operator-(const Point &p) const {
            return Point(_x - p.x(), _y - p.y(), _z - p.z());
        }

        Point operator+(const Point &p) const {
            return Point(_x + p.x(), _y + p.y(), _z + p.z());
        }

        Point operator*(const float &f) const {
            return Point(_x * f, _y * f, _z * f);
        }

        Point operator*(const Point &p) const {
            return Point(_x * p.x(), _y * p.y(), _z * p.z());
        }

        Point operator/(const float &f) const {
            return Point(_x / f, _y / f, _z / f);
        }

        Point operator-() const {
            return Point(-_x, -_y, -_z);
        }
};

#endif