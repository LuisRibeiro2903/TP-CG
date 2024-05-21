#ifndef PARSER_CPP
#define PARSER_CPP

#include <array>
#include <string>
#include <vector>

#include "engine/lights/light.hpp"
#include "groups.hpp"
#include "point.hpp"

using std::vector, std::string;

class ParsedWorld {
public:
  int windowWidth;
  int windowHeight;
  std::array<Point, 3> lookAt;
  std::array<float, 3> projection;
  vector<Light *> lights;
  int n_lights;
  GroupNode *rootGroup;

  ParsedWorld(std::array<Point, 3> &lookAt, std::array<float, 3> &projection,
              int windowWidth, int windowHeight, GroupNode *rootGroup,
              vector<Light *> lights, int n_lights);

  ParsedWorld(const char *filename);
};

ParsedWorld *worldParser(const char *filename);

#endif
