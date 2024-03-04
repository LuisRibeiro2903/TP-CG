#ifndef POINT_HPP
#define POINT_HPP

class Point {
    private:
        float _x, _y, _z;
    
    public:

        Point(float x, float y, float z);

        float x() const;
        float y() const;
        float z() const;
};

#endif