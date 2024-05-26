#include <cmath>


#include "engine/frustum/frustumG.hpp"
#include "cgmath.hpp"
#include <GL/glut.h>

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

    tang = (float)tan(0.5 * angle);
    nh = nearD * tang;
    nw = nh * ratio;
    fh = farD * tang;
    fw = fh * ratio;

}

void FrustumG::setCamDef(float pX, float pY, float pZ, float lX, float lY, float lZ, float uX, float uY, float uZ) {

    Point p(pX, pY, pZ);
    Point l(lX, lY, lZ);
    Point u(uX, uY, uZ);
    Point dir, nc, fc, X, Y, Z;

    Z = p - l;
    Z.normalize();


    cross(u, Z, X);
    X.normalize();

    cross(Z, X, Y);

    nc = p - Z * nearD;
    fc = p - Z * farD;

    ntl = nc + Y * nh - X * nw;
    ntr = nc + Y * nh + X * nw;
    nbl = nc - Y * nh - X * nw;
    nbr = nc - Y * nh + X * nw;
    
    ftl = fc + Y * fh - X * fw;
    ftr = fc + Y * fh + X * fw;
    fbl = fc - Y * fh - X * fw;
    fbr = fc - Y * fh + X * fw;

    pl[TOP].set3Points(ntr, ntl, ftl);
    pl[BOTTOM].set3Points(nbl, nbr, fbr);
    pl[LEFT].set3Points(ntl, nbl, fbl);
    pl[RIGHT].set3Points(nbr, ntr, fbr);
    pl[NEARP].set3Points(ntl, ntr, nbr);
    pl[FARP].set3Points(ftr, ftl, fbl);
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

    for (int i = 0; i < 6; i++) {

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

void FrustumG::drawNormals() {
    Point a, b;

    glColor3f(1.0f, 0.0f, 0.0f);
    //near plane
    a = (ntl + ntr + nbr + nbl) * 0.25;
    b = a + pl[NEARP].normal();
    glBegin(GL_LINES);
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
    glEnd();

    //far plane
    a = (ftl + ftr + fbr + fbl) * 0.25;
    b = a + pl[FARP].normal();
    glBegin(GL_LINES);
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
    glEnd();

    //bottom plane
    a = (nbl + nbr + fbr + fbl) * 0.25;
    b = a + pl[BOTTOM].normal();
    glBegin(GL_LINES);
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
    glEnd();

    //top plane
    a = (ntr + ntl + ftl + ftr) * 0.25;
    b = a + pl[TOP].normal();
    glBegin(GL_LINES);
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
    glEnd();

    //left plane
    a = (ntl + nbl + fbl + ftl) * 0.25;
    b = a + pl[LEFT].normal();
    glBegin(GL_LINES);
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
    glEnd();

    //right plane
    a = (ntr + nbr + fbr + ftr) * 0.25;
    b = a + pl[RIGHT].normal();
    glBegin(GL_LINES);
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
    glEnd();

}

void FrustumG::drawFrustum(bool debugNormals) {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_LINE_LOOP);

    //near plane
        glVertex3f(ntl.x(),ntl.y(),ntl.z());
        glVertex3f(ntr.x(),ntr.y(),ntr.z());
        glVertex3f(nbr.x(),nbr.y(),nbr.z());
        glVertex3f(nbl.x(),nbl.y(),nbl.z());

    glEnd();


    glBegin(GL_LINE_LOOP);
    //far plane
        glVertex3f(ftr.x(),ftr.y(),ftr.z());
        glVertex3f(ftl.x(),ftl.y(),ftl.z());
        glVertex3f(fbl.x(),fbl.y(),fbl.z());
        glVertex3f(fbr.x(),fbr.y(),fbr.z());

    glEnd();

    glBegin(GL_LINE_LOOP);

    //bottom plane
        glVertex3f(nbl.x(),nbl.y(),nbl.z());
        glVertex3f(nbr.x(),nbr.y(),nbr.z());
        glVertex3f(fbr.x(),fbr.y(),fbr.z());
        glVertex3f(fbl.x(),fbl.y(),fbl.z());

    glEnd();


    glBegin(GL_LINE_LOOP);
    //top plane
        glVertex3f(ntr.x(),ntr.y(),ntr.z());
        glVertex3f(ntl.x(),ntl.y(),ntl.z());
        glVertex3f(ftl.x(),ftl.y(),ftl.z());
        glVertex3f(ftr.x(),ftr.y(),ftr.z());

    glEnd();


    glBegin(GL_LINE_LOOP);

    //left plane

        glVertex3f(ntl.x(),ntl.y(),ntl.z());
        glVertex3f(nbl.x(),nbl.y(),nbl.z());
        glVertex3f(fbl.x(),fbl.y(),fbl.z());
        glVertex3f(ftl.x(),ftl.y(),ftl.z());

    glEnd();

    glBegin(GL_LINE_LOOP);
    // right plane
        glVertex3f(nbr.x(),nbr.y(),nbr.z());
        glVertex3f(ntr.x(),ntr.y(),ntr.z());
        glVertex3f(ftr.x(),ftr.y(),ftr.z());
        glVertex3f(fbr.x(),fbr.y(),fbr.z());

    glEnd();

    if (debugNormals) {
        this->drawNormals();
    }

    glEnable(GL_LIGHTING);
}