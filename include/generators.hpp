#include "point.hpp"
#include <vector>

std::vector<Point> generatePlane(float length, int divisions);

std::vector<Point> generateSphere(float radius, int slices, int stacks);

std::vector<Point> generateBox(float dimension, int divisions);
