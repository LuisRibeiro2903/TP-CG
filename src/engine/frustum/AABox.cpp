#include "engine/frustum/AABox.hpp"

#include "cgmath.hpp"

#include <GL/glut.h>

AABox::AABox(Point &Omin, Point &Omax) : Omin(Omin), Omax(Omax) {
  Emin = Omin;
  Emax = Omax;
}

AABox::AABox() {}

AABox::~AABox()
{
}



Point AABox::getVertexP(const Point &normal) {

    Point result;

    result.setX(normal.x() > 0 ? Emax.x() : Emin.x());
    result.setY(normal.y() > 0 ? Emax.y() : Emin.y());
    result.setZ(normal.z() > 0 ? Emax.z() : Emin.z());

    return result;

}

Point AABox::getVertexN(const Point &normal) {

    Point result;

    result.setX(normal.x() > 0 ? Emin.x() : Emax.x());
    result.setY(normal.y() > 0 ? Emin.y() : Emax.y());
    result.setZ(normal.z() > 0 ? Emin.z() : Emax.z());

    return result;
}

std::vector<Point> AABox::generateVertices() {

    std::vector<Point> vertices;

    vertices.push_back(Emin);
    vertices.push_back(Point(Emax.x(), Emin.y(), Emin.z()));
    vertices.push_back(Point(Emax.x(), Emax.y(), Emin.z()));
    vertices.push_back(Point(Emin.x(), Emax.y(), Emin.z()));
    vertices.push_back(Point(Emin.x(), Emin.y(), Emax.z()));
    vertices.push_back(Point(Emax.x(), Emin.y(), Emax.z()));
    vertices.push_back(Emax);
    vertices.push_back(Point(Emin.x(), Emax.y(), Emax.z()));
    
    return vertices;
}

void AABox::draw()
{
    std::vector<Point> vertices = generateVertices();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 4; ++i) {
        glVertex3f(vertices[i].x(), vertices[i].y(), vertices[i].z());
        glVertex3f(vertices[i + 4].x(), vertices[i + 4].y(), vertices[i + 4].z());
    }
    for (int i = 0; i < 4; ++i) {
        glVertex3f(vertices[i].x(), vertices[i].y(), vertices[i].z());
        glVertex3f(vertices[(i + 1) % 4].x(), vertices[(i + 1) % 4].y(), vertices[(i + 1) % 4].z());
    }
    for (int i = 0; i < 4; ++i) {
        glVertex3f(vertices[i + 4].x(), vertices[i + 4].y(), vertices[i + 4].z());
        glVertex3f(vertices[(i + 1) % 4 + 4].x(), vertices[(i + 1) % 4 + 4].y(), vertices[(i + 1) % 4 + 4].z());
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void AABox::reset() {
    Emin = Omin;
    Emax = Omax;
}

void AABox::transform(const float * matrix) {

    Point center = (Omax + Omin) * 0.5;

    Point extents = Omax - center;

    float new_center[4];

    multMatrixVector((float *)matrix, new float[4]{center.x(), center.y(), center.z(), 1}, new_center);

    Point t_center (new_center[0], new_center[1], new_center[2]);

    float abs_matrix[9] = 
    {
        fabs(matrix[0]), fabs(matrix[1]), fabs(matrix[2]),
        fabs(matrix[4]), fabs(matrix[5]), fabs(matrix[6]),
        fabs(matrix[8]), fabs(matrix[9]), fabs(matrix[10])
    };

    float t_extents[3];

    multMatrixVector3(abs_matrix, extents.data(), t_extents);

    Point tmin = t_center - Point(t_extents[0], t_extents[1], t_extents[2]);
    Point tmax = t_center + Point(t_extents[0], t_extents[1], t_extents[2]);

    Emin = tmin;
    Emax = tmax;

}