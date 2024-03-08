#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <point.hpp>
#include <vector>

std::vector<Point> generateCylinder(float radius, float height, int sides) {
  std::vector<Point> points;

  int i;
  float step;

  step = 360.0 / sides;

  glBegin(GL_TRIANGLES);

  // top
  for (i = 0; i < sides; i++) {
    Point p1 = Point(0, height * 0.5, 0);
    Point p2 = Point(cos(i * step * M_PI / 180.0) * radius, height * 0.5,
                     -sin(i * step * M_PI / 180.0) * radius);
    Point p3 = Point(cos((i + 1) * step * M_PI / 180.0) * radius, height * 0.5,
                     -sin((i + 1) * step * M_PI / 180.0) * radius);

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
  }

  // bottom
  for (i = 0; i < sides; i++) {
    Point p1 = Point(0, -height * 0.5, 0);
    Point p2 = Point(cos((i + 1) * step * M_PI / 180.0) * radius, -height * 0.5,
                     -sin((i + 1) * step * M_PI / 180.0) * radius);
    Point p3 = Point(cos(i * step * M_PI / 180.0) * radius, -height * 0.5,
                     -sin(i * step * M_PI / 180.0) * radius);

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
  }

  // body
  for (i = 0; i <= sides; i++) {

    Point p1 = Point(cos(i * step * M_PI / 180.0) * radius, height * 0.5,
                     -sin(i * step * M_PI / 180.0) * radius);
    Point p2 = Point(cos(i * step * M_PI / 180.0) * radius, -height * 0.5,
                     -sin(i * step * M_PI / 180.0) * radius);
    Point p3 = Point(cos((i + 1) * step * M_PI / 180.0) * radius, height * 0.5,
                     -sin((i + 1) * step * M_PI / 180.0) * radius);

    Point p4 = Point(cos(i * step * M_PI / 180.0) * radius, -height * 0.5,
                     -sin(i * step * M_PI / 180.0) * radius);
    Point p5 = Point(cos((i + 1) * step * M_PI / 180.0) * radius, -height * 0.5,
                     -sin((i + 1) * step * M_PI / 180.0) * radius);
    Point p6 = Point(cos((i + 1) * step * M_PI / 180.0) * radius, height * 0.5,
                     -sin((i + 1) * step * M_PI / 180.0) * radius);

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
  }
  glEnd();

  return points;
}
