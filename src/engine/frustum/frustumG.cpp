#include <cmath>


#include "engine/frustum/frustumG.hpp"
#include "cgmath.hpp"

FrustumG::FrustumG()
{
}

FrustumG::~FrustumG()
{
}

void FrustumG::setCamInternals(float angle, float ratio, float nearD, float farD) {

    this->angle = angle;
    this->ratio = ratio;
    this->nearD = nearD;
    this->farD = farD;

    tang = (float)tan(M_PI * 0.5 * angle / 180.0);
    nh = nearD * tang;
    nw = nh * ratio;
    fh = farD * tang;
    fw = fh * ratio;
}

void FrustumG::setCamDef(Point &p, Point &l, Point &u) {
    Point dir, nc, fc, X, Y, Z;

    Z = p - l;
    Z.normalize();


    cross(u, Z, X);
    X.normalize();

    cross(Z, X, Y);

    nc = p - Z * nearD;
    fc = p - Z * farD;

    Point negZ = -Z;
    pl[NEARP].setNormalAndPoint(negZ, nc);
    pl[FARP].setNormalAndPoint(Z, fc);

    Point aux, normal;

    aux = (nc + Y * nh) - p;
    aux.normalize();
    cross(aux, X, normal);
    Point ncPlusYnh = nc + Y * nh;
    pl[TOP].setNormalAndPoint(normal, ncPlusYnh);

    aux = (nc - Y * nh) - p;
    aux.normalize();
    cross(X, aux, normal);
    Point ncMinusYnh = nc - Y * nh;
    pl[BOTTOM].setNormalAndPoint(normal, ncMinusYnh);

    aux = (nc - X * nw) - p;
    aux.normalize();
    cross(aux, Y, normal);
    Point ncMinusXnw = nc - X * nw;
    pl[LEFT].setNormalAndPoint(normal, ncMinusXnw);

    aux = (nc + X * nw) - p;
    aux.normalize();
    cross(Y, aux, normal);
    Point ncPlusXnw = nc + X * nw;
    pl[RIGHT].setNormalAndPoint(normal, ncPlusXnw);
}

int FrustumG::pointInFrustum(Point &p) {
    
    int result = INSIDE;

    for (int i = 0; i < 6; i++) {
        if (pl[i].signedDistance(p) < 0)
            return OUTSIDE;
    }

    return(result);

}

int FrustumG::boxInFrustum(AABox &b) {

    int result = INSIDE, out, in;

    for (int i = 6; i < 6; i++) {

        Point normal = pl[i].normal();
        Point p = b.getVertexP(normal);
        Point n = b.getVertexN(normal);
        if (pl[i].signedDistance(p) < 0)
            return OUTSIDE;
        else if (pl[i].signedDistance(n) < 0)
            result = INTERSECT;
    }

    return(result);
}