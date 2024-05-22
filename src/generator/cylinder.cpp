#include "parsedModel.hpp"
#include <cmath>
#include <point.hpp>

ParsedModel generateCylinder(float radius, float height, int sides) {
  vector<Point> points;
  vector<Point> normals;
  vector<Point> texture;

  float step = 2 * M_PI / sides;
  float step_tex_hor = 1.0f / sides;

  float cur_x, next_x, next_x_texture_side, next_x_texture_top,
      next_x_texture_bot, cur_z, next_z, top_y, bot_y, next_x_normal,
      next_z_normal, next_x_text, next_y_text;
  top_y = height * 0.5;
  bot_y = -top_y;
  next_z = 0;
  next_x = radius;

  Point center_top = Point(0, top_y, 0);
  Point center_bot = Point(0, bot_y, 0);
  Point left_top;
  Point left_top_normal;
  Point left_top_texture;
  Point left_bot;
  Point left_bot_normal;
  Point left_bot_texture;
  Point right_top = Point(next_x, top_y, next_z);
  Point right_top_normal = Point(1, 0, 0);
  Point right_top_texture = Point(0, 1, 0);
  Point right_bot = Point(next_x, bot_y, next_z);
  Point right_bot_normal = Point(1, 0, 0);
  Point right_bot_texture = Point(0, 0.375f, 0);
  // Texture Specific
  Point lower_top_texture;
  Point higher_top_texture = Point(0.625f, 0.1875f, 0);
  Point lower_bot_texture;
  Point higher_bot_texture = Point(1.0f, 0.1875f, 0);

  for (int i = 1; i <= sides; i++) {
    next_x = cos(i * step) * radius;
    next_x_normal = cos(i * step);
    next_x_texture_side = next_z = -sin(i * step) * radius;
    next_z_normal = -sin(i * step);
    next_x_text = 0.4375f + (cos(i * step) * 0.1875f);
    next_y_text = 0.1875 + (sin(i * step) * 0.1875f);

    // take data from last iteration
    left_top = right_top;
    left_top_normal = right_top_normal;
    left_top_texture = right_top_texture;
    left_bot = right_bot;
    left_bot_normal = right_bot_normal;
    left_bot_texture = right_bot_texture;
    lower_bot_texture = higher_bot_texture;
    lower_top_texture = higher_top_texture;

    // calc new points
    right_top = Point(next_x, top_y, next_z);
    right_top_normal = Point(next_x_normal, 0, next_z_normal);
    right_top_texture = Point(next_x_texture_side, 1, 0);
    right_bot = Point(next_x, bot_y, next_z);
    right_bot_normal = Point(next_x_normal, 0, next_z_normal);
    right_bot_texture = Point(next_x_texture_side, 0.375f, 0);
    higher_top_texture = Point(next_x_text, next_y_text, 0);
    lower_bot_texture = Point(next_x_text + 0.375, next_y_text, 0);

    // top
    points.push_back(center_top);
    normals.emplace_back(0, 1, 0);
    texture.emplace_back(0.4375f, 0.1875f, 0);
    points.push_back(left_top);
    normals.emplace_back(0, 1, 0);
    texture.emplace_back(lower_top_texture);
    points.push_back(right_top);
    normals.emplace_back(0, 1, 0);
    texture.emplace_back(higher_top_texture);

    // bottom
    points.push_back(center_bot);
    normals.emplace_back(0, -1, 0);
    texture.emplace_back(0.8125f, 0.1875f, 0);
    points.push_back(right_bot);
    normals.emplace_back(0, -1, 0);
    texture.emplace_back(lower_bot_texture);
    points.push_back(left_bot);
    normals.emplace_back(0, -1, 0);
    texture.emplace_back(higher_bot_texture);

    // body
    points.push_back(left_top);
    normals.push_back(left_top_normal);
    texture.push_back(left_top_texture);
    points.push_back(left_bot);
    normals.push_back(left_bot_normal);
    texture.push_back(left_bot_texture);
    points.push_back(right_top);
    normals.emplace_back(right_top_normal);
    texture.push_back(right_top_texture);
    points.push_back(left_bot);
    normals.push_back(left_bot_normal);
    texture.push_back(left_bot_texture);
    points.push_back(right_bot);
    normals.push_back(right_bot_normal);
    texture.push_back(right_bot_texture);
    points.push_back(right_top);
    normals.push_back(right_top_normal);
    texture.push_back(right_top_texture);
  }

  return ParsedModel(points, normals, texture);
}
