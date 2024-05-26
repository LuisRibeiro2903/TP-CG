#ifndef CGMATH_HPP
#define CGMATH_HPP

#include <math.h>
#include <vector>
#include <point.hpp>

using namespace std;

void buildRotMatrix(float *x, float *y, float *z, float *m);
void cross(float *a, float *b, float *res);
void cross(Point a, Point b, Point& res);
void normalize(float *a);
void normalize(Point& p);
Point normalize2(Point& p);
float length(float *v);
void multMatrixVector(float *m, float *v, float *res);
void multMatrixVector3(float *m, float *v, float *res);
void multiply(float * mat1, float * mat2, float * res);
void transpose(float *m, float *mt);
vector<vector<Point>> MP (vector<vector<float>> m, vector<vector<Point>> p);
vector<vector<Point>> PMtranspose (vector<vector<Point>> p, vector<vector<float>> mt);
vector<Point> uVectorMPMt (float * uVector, vector<vector<Point>> MPMt);
Point uVectorMPMtVVector (vector<Point> uVectorMPMt, float * vVector);

#endif