#ifndef CATMULLROM
#define CATMULLROM

#include "engine/transform/transform.hpp"
#include <vector>
#include <math.h>
#include "point.hpp"
#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "cgmath.hpp"


class CatmullROM : public Transform {
private:
    vector<Point> points;
    int POINT_COUNT;
    float time;
    bool align;
    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) const;
    void renderCatmullRomCurve() const;
    void getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float *pos, float *deriv) const;
    

public:
  CatmullROM(vector<Point> points, float time, bool align);
  void applyTransform() const override;
};

#endif
