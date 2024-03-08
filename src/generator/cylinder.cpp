#include <cmath>
#include <point.hpp>
#include <vector>

std::vector<Point> generateCylinder(float radius, float height, int sides) {
  std::vector<Point> points;

  int i;
  float step;

  step = 2 * M_PI / sides;

  float cur_x, next_x, cur_z, next_z, top_y, bot_y;
  top_y = height * 0.5;
  bot_y = -top_y;

  for (i = 0; i < sides; i++) {
    cur_x = cos(i * step) * radius;
    next_x = cos((i + 1) * step) * radius;
    cur_z = -sin(i * step) * radius;
    next_z = -sin((i + 1) * step) * radius;

    // top
    Point p1 = Point(0, top_y, 0);
    Point p2 = Point(cur_x, top_y, cur_z);
    Point p3 = Point(next_x, top_y, next_z);

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    // bottom
    p1 = Point(0, bot_y, 0);
    p2 = Point(cur_x, bot_y, cur_z);
    p3 = Point(next_x, bot_y, next_z);

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    // body

    p1 = Point(cur_x, top_y, cur_z);
    p2 = Point(cur_x, bot_y, cur_z);
    p3 = Point(next_x, top_y, next_z);

    Point p4 = Point(cur_x, bot_y, cur_z);
    Point p5 = Point(next_x, bot_y, next_z);
    Point p6 = Point(next_x, top_y, next_z);

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
  }
  return points;
}
