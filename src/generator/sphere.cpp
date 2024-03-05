#include "point.hpp"
#include <cmath>
#include <vector>

std::vector<Point> generateSphere(float radius, int slices, int stacks) {
  std::vector<Point> points;

  for (int stack = 0; stack <= stacks; ++stack) {
    float phi = M_PI * stack / stacks;

    for (int slice = 0; slice < slices; ++slice) {
      float theta = 2 * M_PI * slice / slices;

      float x = radius * std::sin(phi) * std::cos(theta);
      float y = radius * std::cos(phi);
      float z = radius * std::sin(phi) * std::sin(theta);

      points.push_back(Point(x, y, z));
    }
  }

  return points;
}
