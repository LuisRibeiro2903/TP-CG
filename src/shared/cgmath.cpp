#include "cgmath.hpp"

void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

void cross(Point a, Point b, Point& res) {

    res.setX(a.y()*b.z() - a.z()*b.y());
    res.setY(a.z()*b.x() - a.x()*b.z());
    res.setZ(a.x()*b.y() - a.y()*b.x());
}

void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

void normalize(Point& p) {

    float l = sqrt(p.x()*p.x() + p.y() * p.y() + p.z() * p.z());

    p.setX(p.x()/l);
    p.setY(p.y()/l);
    p.setZ(p.z()/l);
}

Point normalize2(Point& p) {

    float l = sqrt(p.x()*p.x() + p.y() * p.y() + p.z() * p.z());

   return Point(p.x()/l, p.y()/l, p.z()/l);
}


float length(float *v) {

	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;

}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void multiply(float * mat1,
              float * mat2,
              float * res) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            res[i * 4 + j] = 0;
            for (k = 0; k < 4; k++)
                res[i * 4 + j] += mat1[i * 4 + k] * mat2[k * 4 + j];
        }
    }
}


// The functions below are used in the patch.cpp file in the context of bezier surfaces.
// The names of the functions are based on the class notes pdf:
// p(u, v) = [u^3, u^2, u, 1] * M * P * M^t * [v^3, v^2, v, 1]^t

vector<vector<Point>> MP (vector<vector<float>> m, vector<vector<Point>> p) {
    vector<vector<Point>> res(4, vector<Point>(4));

    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            float x = 0;
            float y = 0;
            float z = 0;
            for (int k = 0; k < 4; k++) {
                x += m[i][k] * p[k][j].x();
                y += m[i][k] * p[k][j].y();
                z += m[i][k] * p[k][j].z();
            }
            res[i][j] = Point(x, y, z);
        }
    }
    return res;

}


vector<vector<Point>> PMtranspose (vector<vector<Point>> p, vector<vector<float>> mt) {
    vector<vector<Point>> res(4, vector<Point>(4));

    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float x = 0;
            float y = 0;
            float z = 0;
            for (int k = 0; k < 4; k++) {
                x += p[i][k].x() * mt[k][j];
                y += p[i][k].y() * mt[k][j];
                z += p[i][k].z() * mt[k][j];
            }
            res[i][j] = Point(x, y, z);
        }
    }

    return res;
}

vector<Point> uVectorMPMt (float * uVector, vector<vector<Point>> MPMt) {
    vector<Point> res(4);

    for(int i = 0; i < 4; i++) {
        float x = 0;
        float y = 0;
        float z = 0;
        for (int j = 0; j < 4; j++) {
            x += uVector[j] * MPMt[j][i].x();
            y += uVector[j] * MPMt[j][i].y();
            z += uVector[j] * MPMt[j][i].z();
        }
        res[i] = Point(x, y, z);
    }

    return res;
}


Point uVectorMPMtVVector (vector<Point> uVectorMPMt, float * vVector) {
    
    float x = 0;
    float y = 0;
    float z = 0;
    
    for(int i = 0; i < 4; i++) {
        x += uVectorMPMt[i].x() * vVector[i];
        y += uVectorMPMt[i].y() * vVector[i];
        z += uVectorMPMt[i].z() * vVector[i];
    }

    return Point(x, y, z);
}
