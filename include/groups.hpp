#ifndef GROUPS
#define GROUPS

#include "engine/transform/transform.hpp"
#include "engine/frustum/frustumG.hpp"
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


  void buildTransformationMatrix(float * matrix, float *matrixToAABox);

public:
  GroupNode(vector<GroupNode *> &_sub_nodes, vector<Transform *> &_transforms,
            vector<Model *> &_models);
  GroupNode();
  void draw(bool debugNormals, bool frustumOn, int * modelosDesenhados, FrustumG *frustum, float * matrixToAABox, char * name, Point &fixedCenter);
  void initVBOs();
  void addTransform(Transform *transform);
  void addModel(Model *m);
  int totalModels();
  vector<string *> getNames();
  void addSubNode(GroupNode *node);
  void drawAABox();
  void resetAABox();
};

#endif
