#ifndef AABOX_HPP
#define AABOX_HPP

#include "point.hpp"

#include <vector>

class AABox {
    public:
        Point corner;
        float x, y, z;

        AABox(Point &corner, float x, float y, float z);
        AABox();
        ~AABox();

        void setBox(Point &corner, float x, float y, float z);

        Point getVertexP(const Point &normal);
        Point getVertexN(const Point &normal);

        //These functions are used for debugging purposes
        std::vector<Point> generateVertices();
        void draw();

};


#endif