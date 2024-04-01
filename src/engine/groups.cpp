#include <vector>

class Transform {
  int temp;
};

class Model {
  int temp;
};

class GroupNode {
  std::vector<GroupNode> sub_nodes;
  std::vector<Transform> transforms;
  std::vector<Model> models;

public:
  GroupNode(std::vector<GroupNode> subNodes, std::vector<Transform> transforms,
            std::vector<Model> models)
      : sub_nodes(std::move(sub_nodes)), transforms(std::move(transforms)),
        models(std::move(models)) {}
};
