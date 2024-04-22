#include "engine/transform/catmullrom.hpp" 

CatmullROM::CatmullROM(vector<Point> points, float time, bool align)
    : points(points), time(time), align(align) {
        POINT_COUNT = points.size();
    }


void CatmullROM::getCatmullRomPoint(float t, Point pp0, Point pp1, Point pp2, Point pp3, float *pos, float *deriv) const{

    float m[4][4] = {   {-0.5f,  1.5f, -1.5f,  0.5f},
                        { 1.0f, -2.5f,  2.0f, -0.5f},
                        {-0.5f,  0.0f,  0.5f,  0.0f},
                        { 0.0f,  1.0f,  0.0f,  0.0f}};

    float p0[3] = {pp0.x(), pp0.y(), pp0.z()};
    float p1[3] = {pp1.x(), pp1.y(), pp1.z()};
    float p2[3] = {pp2.x(), pp2.y(), pp2.z()};
    float p3[3] = {pp3.x(), pp3.y(), pp3.z()};

    for(int i = 0; i < 3; i++) {
		float A[4];
		float P[4] = {p0[i], p1[i], p2[i], p3[i]};
		float T[4] = {t*t*t, t*t, t};
		float derivT[4] = {3*t*t, 2*t};
		multMatrixVector((float *)m, P, A);
		pos[i] = T[0]*A[0] + T[1]*A[1] + T[2]*A[2] + A[3];
		deriv[i] = derivT[0]*A[0] + derivT[1]*A[1] + A[2];
	}

}


void CatmullROM::getGlobalCatmullRomPoint(float gt, float * pos, float* deriv) const {
    float t = gt * POINT_COUNT;
    int index = floor(t);
    t = t - index;


    int indices[4];

    indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
    indices[1] = (indices[0] + 1) % POINT_COUNT;
    indices[2] = (indices[1] + 1) % POINT_COUNT;
    indices[3] = (indices[2] + 1) % POINT_COUNT;

    getCatmullRomPoint(t, points[indices[0]], points[indices[1]], points[indices[2]], points[indices[3]], pos, deriv);
}



void CatmullROM::renderCatmullRomCurve() const{
    float pos[3], deriv[3];

    // draw curve using line segments with GL_LINE_LOOP
    // the higher the tesselation, the smoother the curve
    float t1 = 64.0f;
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < t1; i++)
    {
        getGlobalCatmullRomPoint(i/t1, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}



void CatmullROM::applyTransform() const {

    float m[16];
    float pos[3], deriv[3];
    //TODO: alterar este valor de static para específico á curva
    static float prev_y[3] = {0, 1, 0};
    renderCatmullRomCurve();

    float t = ((float) glutGet(GLUT_ELAPSED_TIME) / 1000 ) / time;

    getGlobalCatmullRomPoint(t, pos, deriv);

    glTranslatef(pos[0], pos[1], pos[2]);

    float X[3] = {deriv[0], deriv[1], deriv[2]};
    normalize(X);

    float Z[3];
    cross(X, prev_y, Z);
    normalize(Z);

    float Y[3];
    cross(Z, X, Y);
    normalize(Y);

    memcpy(prev_y, Y, 3*sizeof(float));

    buildRotMatrix(X, Y, Z, m);

    glMultMatrixf(m);



}

