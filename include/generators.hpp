#include "point.hpp"
#include "parsedModel.hpp"
#include <string>
#include <vector>

ParsedModel generatePlane(float length, int divisions);
ParsedModel generateSphere(float radius, int slices, int stacks);
ParsedModel generateBox(float dimension, int divisions);
ParsedModel generateCone(float radius, float height, int slices, int stacks);
ParsedModel generateCylinder(float radius, float height, int sides);
ParsedModel generatePatch(std::string &patchfile, float tesselationLevel);
