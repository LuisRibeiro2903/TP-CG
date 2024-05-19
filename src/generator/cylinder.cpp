#include <cmath>
#include <point.hpp>
#include <vector>
#include "parsedModel.hpp"

ParsedModel generateCylinder(float radius, float height, int sides) {
  std::vector<Point> points;
  std::vector<Point> normals;

  int i;
  float step;

  step = 2 * M_PI / sides;

  float cur_x, next_x, cur_z, next_z, top_y, bot_y, next_x_normal, next_z_normal;
  top_y = height * 0.5;
  bot_y = -top_y;
  next_z = 0;
  next_x = radius;

  Point center_top = Point(0, top_y, 0);
  Point center_bot = Point(0, bot_y, 0);
  Point left_top;
  Point left_top_normal;
  Point left_bot;
  Point left_bot_normal;
  Point right_top = Point(next_x, top_y, next_z);
  Point right_top_normal = Point(1, 0, 0);
  Point right_bot = Point(next_x, bot_y, next_z);
  Point right_bot_normal = Point(1, 0, 0);

  for (i = 1; i <= sides; i++) {
    // take data from last iteration
    next_x = cos(i * step) * radius;
    next_x_normal = cos(i * step);
    next_z = -sin(i * step) * radius;
    next_z_normal = -sin(i * step);

    left_top = right_top;
    left_top_normal = right_top_normal;
    left_bot = right_bot;
    left_bot_normal = right_bot_normal;

    // calc new points
    right_top = Point(next_x, top_y, next_z);
    right_top_normal = Point(next_x_normal, 0 , next_z_normal);
    right_bot = Point(next_x, bot_y, next_z);
    right_bot_normal = Point(next_x_normal, 0, next_z_normal);

    // top
    points.push_back(center_top);
    normals.emplace_back(0, 1, 0);
    points.push_back(left_top);
    normals.emplace_back(0, 1, 0);
    points.push_back(right_top);
    normals.emplace_back(0, 1, 0);

    // bottom
    points.push_back(center_bot);
    normals.emplace_back(0, -1, 0);
    points.push_back(right_bot);
    normals.emplace_back(0, -1, 0);
    points.push_back(left_bot);
    normals.emplace_back(0, -1, 0);

    // body
    points.push_back(left_top);
    normals.push_back(left_top_normal);
    points.push_back(left_bot);
    normals.push_back(left_bot_normal);
    points.push_back(right_top);
    normals.emplace_back(right_top_normal);
    points.push_back(left_bot);
    normals.push_back(left_bot_normal);
    points.push_back(right_bot);
    normals.push_back(right_bot_normal);
    points.push_back(right_top);
    normals.push_back(right_top_normal);
  }

  return ParsedModel(points, normals, {});
}
