#ifndef GROUPS
#define GROUPS

#include "engine/transform/transform.hpp"
#include "model.hpp"
#include "parsedModel.hpp"
#include <GL/glew.h>
#include <array>
#include <string>
#include <vector>

using std::vector, std::string, std::array;

class GroupNode {
private:
  vector<GroupNode *> sub_nodes;
  vector<Transform *> transforms;
  vector<Model *> models;

public:
  GroupNode(vector<GroupNode *> &_sub_nodes, vector<Transform *> &_transforms,
            vector<Model *> &_models);
  GroupNode();
  void draw(bool debugNormals);
  void initVBOs();
  void addTransform(Transform *transform);
  void addModel(Model *m);
  void addSubNode(GroupNode *node);
};

#endif
