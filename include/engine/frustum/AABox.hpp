#ifndef AABOX_HPP
#define AABOX_HPP

#include "point.hpp"

#include <vector>

class AABox {
    public:
        Point Ocorner;
        float Ox, Oy, Oz;
        Point efective_corner;
        float efective_x, efective_y, efective_z;

        AABox(Point &corner, float x, float y, float z);
        AABox();
        ~AABox();

        Point getVertexP(const Point &normal);
        Point getVertexN(const Point &normal);
        void translate(float x, float y, float z);
        void scale(float x, float y, float z);

        //These functions are used for debugging purposes
        std::vector<Point> generateVertices();
        void draw();

};


#endif