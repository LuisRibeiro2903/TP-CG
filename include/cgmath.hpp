#ifndef CGMATH_HPP
#define CGMATH_HPP

#include <math.h>
#include <vector>
#include <point.hpp>

using namespace std;

void buildRotMatrix(float *x, float *y, float *z, float *m);
void cross(float *a, float *b, float *res);
void normalize(float *a);
float length(float *v);
void multMatrixVector(float *m, float *v, float *res);
void multiply(float * mat1, float * mat2, float * res);
vector<vector<Point>> MP (vector<vector<float>> m, vector<vector<Point>> p);
vector<vector<Point>> PMtranspose (vector<vector<Point>> p, vector<vector<float>> mt);
vector<Point> uVectorMPMt (float * uVector, vector<vector<Point>> MPMt);
Point uVectorMPMtVVector (vector<Point> uVectorMPMt, float * vVector);

#endif