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
        
    public:
        enum {OUTSIDE, INTERSECT, INSIDE};
        Plane pl[6];
        Point ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
        float nearD, farD, ratio, angle, tang;
        float nw, nh, fw, fh;

        FrustumG();
        ~FrustumG();

        void setCamInternals(float angle, float ratio, float nearD, float farD);
        void setCamDef(Point &p, Point &l, Point &u);
        int pointInFrustum(Point &p);
        int sphereInFrustum(Point &p, float radius);
        int boxInFrustum(AABox &b);
};

#endif