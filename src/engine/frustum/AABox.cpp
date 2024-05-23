#include "engine/frustum/AABox.hpp"
#include "point.hpp"

#include <GL/glut.h>

AABox::AABox(Point &corner, float x, float y, float z)
{
    this->Ocorner = corner;
    this->Ox = x;
    this->Oy = y;
    this->Oz = z;
    this->efective_corner = corner;
    this->efective_x = x;
    this->efective_y = y;
    this->efective_z = z;
}

AABox::AABox()
{
    Ocorner = Point();
    Ox = 1.0f;
    Oy = 1.0f;
    Oz = 1.0f;
    efective_corner = Ocorner;
    efective_x = Ox;
    efective_y = Oy;
    efective_z = Oz;
}

AABox::~AABox()
{
}



Point AABox::getVertexP(const Point &normal)
{
    Point res = efective_corner;
    if (normal.x() > 0) res.setX(res.x() + efective_x);
    if (normal.y() > 0) res.setY(res.y() + efective_y);
    if (normal.z() > 0) res.setZ(res.z() + efective_z);

    return res;
}

Point AABox::getVertexN(const Point &normal)
{
    Point res = efective_corner;
    if (normal.x() < 0) res.setX(res.x() + efective_x);
    if (normal.y() < 0) res.setY(res.y() + efective_y);
    if (normal.z() < 0) res.setZ(res.z() + efective_z);

    return res;
}

std::vector<Point> AABox::generateVertices()
{
    std::vector<Point> res;
    res.push_back(efective_corner);
    res.push_back(Point(efective_corner.x() + efective_x, efective_corner.y(), efective_corner.z()));
    res.push_back(Point(efective_corner.x() + efective_x, efective_corner.y() + efective_y, efective_corner.z()));
    res.push_back(Point(efective_corner.x(), efective_corner.y() + efective_y, efective_corner.z()));
    res.push_back(Point(efective_corner.x(), efective_corner.y(), efective_corner.z() + efective_z));
    res.push_back(Point(efective_corner.x() + efective_x, efective_corner.y(), efective_corner.z() + efective_z));
    res.push_back(Point(efective_corner.x() + efective_x, efective_corner.y() + efective_y, efective_corner.z() + efective_z));
    res.push_back(Point(efective_corner.x(), efective_corner.y() + efective_y, efective_corner.z() + efective_z));

    return res;
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

void AABox::translate(float x, float y, float z)
{
    efective_corner.setX(Ocorner.x() + x);
    efective_corner.setY(Ocorner.y() + y);
    efective_corner.setZ(Ocorner.z() + z);
}

void AABox::scale(float x, float y, float z)
{
    efective_corner = Ocorner * Point(x, y, z);
    efective_x = Ox * x;
    efective_y = Oy * y;
    efective_z = Oz * z;
}