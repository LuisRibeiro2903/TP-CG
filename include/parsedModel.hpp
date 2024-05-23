#ifndef PARSEDMODEL_HPP
#define PARSEDMODEL_HPP

#include "point.hpp"
#include <GL/glew.h>
#include <string>
#include <vector>

using std::vector, std::string;

class ParsedModel {

private:
  vector<Point> vertex;
  vector<Point> normals;
  vector<Point> textures;

public:
  ParsedModel(vector<Point> vertex, vector<Point> normals,
              vector<Point> textures);
  ParsedModel(string *file_name, bool has_textures);

  vector<Point> getVertex();
  vector<Point> getNormals();
  vector<Point> getTextures();
};

#endif
