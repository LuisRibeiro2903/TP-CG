#include "engine/transform/transform.hpp"
#include "parser.hpp"

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
