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

void GroupNode::draw() {
  glPushMatrix();

  for (Transform *t : transforms) {
    t->applyTransform();
  }

  for (Model *m : models) {
    m->draw();
  }

  for (GroupNode *node : sub_nodes) {
    node->draw();
  }

  glPopMatrix();
}
