#include "point.hpp"
#include <cmath>
#include <vector>

// can be replaced for triang strip draw method
void drawMidStacks(std::vector<Point> points, float radius, int stacks,
                   float cur_hor, float next_hor, float ver_step) {
  float cur_ver, next_ver;
  next_ver = 90.0f - ver_step;
  for (int i = 2; i < stacks; i++) {
    cur_ver = next_ver;
    next_ver = 90.0f - i * ver_step;

    // triangle with 2 points on top
    Point p1(radius * cos(cur_hor), radius * sin(cur_ver),
             radius * sin(cur_hor));
    Point p2(radius * cos(next_hor), radius * sin(cur_ver),
             radius * sin(next_hor));
    Point p3(radius * cos(cur_hor), radius * sin(next_ver),
             radius * sin(cur_hor));

    // triangle with 2 points on bot
    Point p4(radius * cos(next_hor), radius * sin(cur_ver),
             radius * sin(next_hor));
    Point p5(radius * cos(cur_hor), radius * sin(next_ver),
             radius * sin(cur_hor));
    Point p6(radius * cos(next_hor), radius * sin(next_ver),
             radius * sin(next_hor));

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
  }
}

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

    // draw mid part if any
    if (stacks > -2) {
      for (int i = 0; i < stacks; i++) {
        drawMidStacks(points, radius, stacks, angle_cur_hor, angle_next_hor,
                      angle_step_ver);
      }
    }
  }

  return points;
}
