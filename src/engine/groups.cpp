#include "groups.hpp"
#include "engine/transform/transform.hpp"
#include "parsedModel.hpp"
#include "parser.hpp"
#include <engine/color.hpp>
#include <engine/transform/transform.hpp>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

void GroupNode::addTransform(Transform *transform) {
  transforms.push_back(transform);
}

void GroupNode::addModel(Model *m) { models.push_back(m); }

void GroupNode::addSubNode(GroupNode *node) { sub_nodes.push_back(node); }

GroupNode::GroupNode(vector<GroupNode *> &_sub_nodes,
                     vector<Transform *> &_transforms, vector<Model *> &_models)
    : sub_nodes(_sub_nodes), transforms(_transforms), models(_models) {}

GroupNode::GroupNode() {}

void GroupNode::initVBOs() {
  for (Model *m : models) {
    m->createVBOS();
  }

  for (GroupNode *node : sub_nodes) {
    node->initVBOs();
  }
}

void GroupNode::buildTransformationMatrix() {

  //Initialize the matrix with the identity matrix
  float matrix[16] = {1, 0, 0, 0, 0, 1, 0, 0,
                      0, 0, 1, 0, 0, 0, 0, 1};

  //Apply the transformations to the matrix
  for (Transform *t : transforms) {
    t->applyTransform(matrix);
  }

  glMultMatrixf(matrix);
}

void GroupNode::draw(bool debugNormals, bool debugBoxes) {
  glPushMatrix();

  buildTransformationMatrix();

  /* for (Transform *t : transforms) 
    for (Model *m : models) 
      m->updateAABox(*t);  

  if (debugBoxes) {
    for (Model *m : models) {
      m->drawAABox();
    }
  } 
  for (Transform *t : transforms)
    t->applyTransform();
  */

  for (Model *m : models) {
    m->draw(debugNormals);
  }

  for (GroupNode *node : sub_nodes) {
    node->draw(debugNormals, debugBoxes);
  }

  glPopMatrix();
}
