#include <model.hpp>
#include <transform.hpp>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class Model {
  int temp;
};

class GroupNode {
  std::vector<GroupNode> sub_nodes;
  std::vector<Transform> transforms;
  std::vector<Model> models;

public:
  GroupNode(std::vector<GroupNode> sub_nodes, std::vector<Transform> transforms,
            std::vector<Model> models)
      : sub_nodes(std::move(sub_nodes)), transforms(std::move(transforms)),
        models(std::move(models)) {}

  void drawNodes() {
    glPushMatrix();

    for (Transform t : transforms) {
      t.applyTransform();
    }

    for (Model m : models) {
      m.drawModel();
    }

    glPopMatrix();
  }
};
