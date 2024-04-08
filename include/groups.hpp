#ifndef GROUPS
#define GROUPS

#include "engine/transform/transform.hpp"
#include <string>
#include <vector>
#include <array>

using std::vector, std::string, std::array;

class GroupNode {
private:
  vector<GroupNode *> sub_nodes;
  vector<Transform *> transforms;
  vector<string *> models;
  array<float, 3> color;

public:
  GroupNode(vector<GroupNode *> &_sub_nodes, vector<Transform *> &_transforms,
            vector<string *> &_models, array<float, 3> &_color);
  GroupNode();
  void draw();

  void addTransform(Transform *transform);
  void addModel(string *model);
  void addSubNode(GroupNode *node);
  void setColor(float r, float g, float b);
};

#endif
