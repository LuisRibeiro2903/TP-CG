#ifndef GROUPS
#define GROUPS

#include "engine/transform/transform.hpp"
#include "engine/color.hpp"
#include <GL/glew.h>
#include <string>
#include <vector>
#include <array>

using std::vector, std::string, std::array;

class GroupNode {
private:
  vector<GroupNode *> sub_nodes;
  vector<Transform *> transforms;
  //TODO: Modificar para uma estrutura de dados sobre um modelo, e aqui guardar um array/vector/pointer de modelos
  vector<string *> models;
  GLuint * model_vbos;
  GLuint * normal_vbos;
  GLuint * normal_line_vbos;
  size_t * model_sizes;
  int n_models;
  vector<Color *> color;

  void drawModels(bool debugNormals);
  void createVBOs();
  void applyColor();

public:
  GroupNode(vector<GroupNode *> &_sub_nodes, vector<Transform *> &_transforms,
            vector<string *> &_models, vector<Color *> _color);
  GroupNode();
  void draw(bool debugNormals);

  void initializeVBOs();


  void addTransform(Transform *transform);
  void addModel(string *model);
  void addSubNode(GroupNode *node);
  void addColor(vector<Color *> color);
};

#endif
