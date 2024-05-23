#ifndef MODEL
#define MODEL

#include "engine/color.hpp"
#include "point.hpp"
#include <string>
#include <vector>

using std::vector, std::string;

class Model {
private:
  vector<Point> model;
  vector<Point> normals;
  vector<Point> texture;
  tuple<GLuint, GLuint, GLuint, GLuint> vbos;
  Color color;
  string *texPath;
  int texID;

  vector<Point> createNormalLineVector();

public:
  Model(vector<Point> _model, vector<Point> _normals, vector<Point> _texture,
        Color *_color, string *texPath);

  void createVBOS();
  vector<Point> getModel() { return model; }
  vector<Point> getNormals() { return normals; }
  vector<Point> getTexture() { return texture; }
  Color getColor() { return color; }

  void draw(bool debugNormals);
  ~Model();
};

#endif
