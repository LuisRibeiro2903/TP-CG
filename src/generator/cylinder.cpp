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
  next_z = 0;
  next_x = radius;

  Point center_top = Point(0, top_y, 0);
  Point center_bot = Point(0, bot_y, 0);
  Point left_top;
  Point left_bot;
  Point right_top = Point(next_x, top_y, next_z);
  Point right_bot = Point(next_x, bot_y, next_z);

  for (i = 1; i <= sides; i++) {
    // take data from last iteration
    next_x = cos(i * step) * radius;
    next_z = -sin(i * step) * radius;

    left_top = right_top;
    left_bot = right_bot;

    // calc new points
    right_top = Point(next_x, top_y, next_z);
    right_bot = Point(next_x, bot_y, next_z);

    // top
    points.push_back(center_top);
    points.push_back(left_top);
    points.push_back(right_top);

    // bottom
    points.push_back(center_bot);
    points.push_back(right_bot);
    points.push_back(left_bot);

    // body
    points.push_back(left_top);
    points.push_back(left_bot);
    points.push_back(right_top);
    points.push_back(left_bot);
    points.push_back(right_bot);
    points.push_back(right_top);
  }
  return points;
}
