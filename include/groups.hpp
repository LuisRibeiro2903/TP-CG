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
  vector<string *> models;
  GLuint * model_vbos;
  size_t * model_sizes;
  int n_models;
  Color * color;

  void drawModels();
  void createVBOs();

public:
  GroupNode(vector<GroupNode *> &_sub_nodes, vector<Transform *> &_transforms,
            vector<string *> &_models, Color *_color);
  GroupNode();
  void draw();

  void initializeVBOs();


  void addTransform(Transform *transform);
  void addModel(string *model);
  void addSubNode(GroupNode *node);
  void addColor(Color *color);
};

#endif
