#ifndef POINT_HPP
#define POINT_HPP

class Point {
    private:
        float _x, _y, _z;
    
    public:

        Point(float x, float y, float z);
        Point();
        Point operator+(const Point& other) const;
        float x() const;
        float y() const;
        float z() const;

        void setX(float x);
        void setY(float y);
        void setZ(float z);
        float * data();
};

#endif