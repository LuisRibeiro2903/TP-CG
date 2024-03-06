
#ifndef BOX_HPP
#define BOX_HPP

#include "point.hpp"
#include <vector>

std::vector<Point> generatePlaneXZ(float dimension, int divisions);
std::vector<Point> generatePlaneXY(float dimension, int divisions);
std::vector<Point> generatePlaneYZ(float dimension, int divisions);

#endif
