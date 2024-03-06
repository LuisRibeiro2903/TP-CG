#ifndef PARSER_CPP
#define PARSER_CPP

#include <vector>
#include <array>

#include "point.hpp"
#include "tinyxml2.h"

using std::vector;

class ParsedWorld {
    public:
        int _windowWidth;
        int _windowHeight;
        std::array<Point, 3> _lookAt;
        std::array<float, 3> _projection;
        std::vector<std::string> _models;

        ParsedWorld(std::array<Point, 3>& lookAt,
                    std::array<float, 3>& projection,
                    int windowWidth,
                    int windowHeight,
                    std::vector<std::string>& models);
};

vector<Point> parse3dFile (const char* filename);

ParsedWorld worldParser (const char* filename);

#endif