#ifndef MODEL
#define MODEL

#include "engine/color.hpp"
#include "point.hpp"
#include <vector>

using std::vector;

class Model {
private:
  vector<Point> model;
  vector<Point> normals;
  vector<Point> texture;
  tuple<GLuint, GLuint, GLuint> vbos;
  Color color;

  tuple<GLuint, GLuint, GLuint> createVBOS();

public:
  Model(vector<Point> *_model, vector<Point> *_normals, vector<Point> *_texture,
        Color *_color);

  vector<Point> getModel() { return model; }
  vector<Point> getNormals() { return normals; }
  vector<Point> getTexture() { return texture; }
  Color getColor() { return color; }

  void draw();
  ~Model();
};

#endif
