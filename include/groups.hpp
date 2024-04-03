#ifndef GROUPS
#define GROUPS

#include "engine/transform/transform.hpp"
#include "string"
#include "vector"

using namespace std;

class GroupNode {
private:
  vector<GroupNode> sub_nodes;
  vector<Transform *> transforms;
  vector<string> models;

public:
  GroupNode(vector<GroupNode> sub_nodes, vector<Transform *> transforms,
            vector<string> models);
  void drawNodes();
};

#endif
