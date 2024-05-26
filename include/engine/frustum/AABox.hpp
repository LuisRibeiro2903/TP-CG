#ifndef AABOX_HPP
#define AABOX_HPP

#include "point.hpp"

#include <vector>

class AABox {
    public:
        Point Omin, Omax;
        Point Emin, Emax;

        AABox(Point &Omin, Point &Omax);
        AABox();
        ~AABox();

        Point getVertexP(const Point &normal);
        Point getVertexN(const Point &normal);
        void transform(const float *matrix);
        void reset();

        //These functions are used for debugging purposes
        std::vector<Point> generateVertices();
        void draw();
        void getCenter(Point &center);

};


#endif