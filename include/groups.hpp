#ifndef GROUPS
#define GROUPS

#include "engine/transform/transform.hpp"
#include "string"
#include "vector"

using namespace std;

class GroupNode {
private:
  vector<GroupNode *> sub_nodes;
  vector<Transform *> transforms;
  vector<string *> models;

public:
  GroupNode(vector<GroupNode *> &_sub_nodes, vector<Transform *> &_transforms,
            vector<string *> &_models);
  void drawNodes();
};

#endif
