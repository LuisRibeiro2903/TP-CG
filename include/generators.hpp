#include "point.hpp"
#include <string>
#include <vector>

std::vector<Point> generatePlane(float length, int divisions);
std::vector<Point> generateSphere(float radius, int slices, int stacks);
std::vector<Point> generateBox(float dimension, int divisions);
std::vector<Point> generateCone(float radius, float height, int slices, int stacks);
std::vector<Point> generateCylinder(float radius, float height, int sides);
std::vector<Point> generatePatch(std::string &patchfile, float tesselationLevel);
