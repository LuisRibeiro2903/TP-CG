#include "point.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

std::vector<Point> generateSphere(float radius, int slices, int stacks) {
  std::vector<Point> points;

  float angle_cur_hor;
  float angle_next_hor;
  float angle_step_hor = 360.0f / (float)slices;
  float angle_cur_ver;
  float angle_next_ver;
  float angle_step_ver = 180.0f / (float)stacks;
  float angle_init_ver = 90.0f - angle_step_ver;

  for (int i = 0; i < slices; i++) {
    // calc hor angle
    angle_cur_hor = i * angle_step_hor;
    angle_next_hor = (i + 1) * angle_step_hor;

    // draw top
    Point t1(0.0f, radius, 0.0f);
    Point t2(radius * cos(angle_cur_hor), radius * sin(angle_init_ver),
             radius * sin(angle_cur_hor));
    Point t3(radius * cos(angle_next_hor), radius * sin(angle_init_ver),
             radius * sin(angle_next_hor));
    points.push_back(t1);
    points.push_back(t2);
    points.push_back(t3);

    // draw bot
    Point b1(0.0f, radius, 0.0f);
    Point b2(radius * cos(angle_next_hor), radius * sin(-angle_init_ver),
             radius * sin(angle_next_hor));
    Point b3(radius * cos(angle_cur_hor), radius * sin(-angle_init_ver),
             radius * sin(angle_next_hor));
    points.push_back(b1);
    points.push_back(b2);
    points.push_back(b3);

    // remove top and bot
    stacks -= 2;
    if (stacks > 0) {
      angle_cur_ver = angle_init_ver;
      for (int i = 0; i < stacks; i++) {
      }
    }
  }

  return points;
}
