#include "engine/frustum/AABox.hpp"
#include "point.hpp"

#include <GL/glut.h>

AABox::AABox(Point &corner, float x, float y, float z)
{
    setBox(corner, x, y, z);
}

AABox::AABox()
{
    corner = Point();
    x = 1.0f;
    y = 1.0f;
    z = 1.0f;
}

AABox::~AABox()
{
}

void AABox::setBox(Point &corner, float x, float y, float z)
{
    this->corner = corner;
    
    if (x < 0) {
        x = -x;
        corner.setX(corner.x() - x);
    }
    if (y < 0) {
        y = -y;
        corner.setY(corner.y() - y);
    }
    if (z < 0) {
        z = -z;
        corner.setZ(corner.z() - z);
    }
    this->x = x;
    this->y = y;
    this->z = z;
}


Point AABox::getVertexP(const Point &normal)
{
    Point res = corner;
    if (normal.x() > 0) res.setX(res.x() + x);
    if (normal.y() > 0) res.setY(res.y() + y);
    if (normal.z() > 0) res.setZ(res.z() + z);

    return res;
}

Point AABox::getVertexN(const Point &normal)
{
    Point res = corner;
    if (normal.x() < 0) res.setX(res.x() + x);
    if (normal.y() < 0) res.setY(res.y() + y);
    if (normal.z() < 0) res.setZ(res.z() + z);

    return res;
}

std::vector<Point> AABox::generateVertices()
{
    std::vector<Point> res;
    res.push_back(corner);
    res.push_back(Point(corner.x() + x, corner.y(), corner.z()));
    res.push_back(Point(corner.x() + x, corner.y() + y, corner.z()));
    res.push_back(Point(corner.x(), corner.y() + y, corner.z()));
    res.push_back(Point(corner.x(), corner.y(), corner.z() + z));
    res.push_back(Point(corner.x() + x, corner.y(), corner.z() + z));
    res.push_back(Point(corner.x() + x, corner.y() + y, corner.z() + z));
    res.push_back(Point(corner.x(), corner.y() + y, corner.z() + z));

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