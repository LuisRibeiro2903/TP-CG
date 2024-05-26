#ifndef FRUSTUMG_HPP
#define FRUSTUMG_HPP

#include "point.hpp"
#include "engine/frustum/plane.hpp"
#include "engine/frustum/AABox.hpp"

class FrustumG {
    private:

        enum {
            TOP = 0, BOTTOM, LEFT,
            RIGHT, NEARP, FARP
        };

        void drawNormals();
        
    public:
        enum {OUTSIDE, INTERSECT, INSIDE};
        Plane pl[6];
        Point ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
        float nearD, farD, ratio, angle, tang;
        float nw, nh, fw, fh;

        FrustumG();
        ~FrustumG();

        void setCamInternals(float angle, float ratio, float nearD, float farD);
        void setCamDef(float pX, float pY, float pZ, float lX, float lY, float lZ, float uX, float uY, float uZ);
        int pointInFrustum(Point &p);
        void drawFrustum(bool debugNormals);
        int boxInFrustum(AABox &b);
};

#endif