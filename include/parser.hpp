#ifndef PARSER_CPP
#define PARSER_CPP

#include <array>
#include <string>
#include <vector>

#include "groups.hpp"
#include "point.hpp"

using std::vector, std::string;

class ParsedWorld {
public:
  int windowWidth;
  int windowHeight;
  std::array<Point, 3> lookAt;
  std::array<float, 3> projection;
  vector<GroupNode *> groups;

  ParsedWorld(std::array<Point, 3> &lookAt, std::array<float, 3> &projection,
              int windowWidth, int windowHeight, vector<GroupNode *> &groups);

  ParsedWorld(const char *filename);
};

vector<vector<Point>> parse3dFile(vector<string> models);

ParsedWorld worldParser(const char *filename);

#endif
