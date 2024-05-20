#include "groups.hpp"
#include "engine/transform/transform.hpp"
#include "parsedModel.hpp"
#include "parser.hpp"
#include "point.hpp"
#include <engine/color.hpp>
#include <engine/transform/transform.hpp>
#include <fstream>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

ParsedModel parse3dFile(string *model) {
  vector<Point> vertices;
  vector<Point> normals;
  vector<Point> textures;

  ifstream file(*model);

  if (!file.is_open()) {
    cerr << "Error: file not found: " << *model << endl;
    exit(1);
  }

  int n_vertices;
  file >> n_vertices;
  for (int i = 0; i < n_vertices; i++) {
    float x, y, z;
    char comma;
    file >> x >> comma >> y >> comma >> z;
    vertices.emplace_back(x, y, z);
  }
  for (int i = 0; i < n_vertices; i++) {
    float x, y, z;
    char comma;
    file >> x >> comma >> y >> comma >> z;
    normals.emplace_back(x, y, z);
  }
  for (int i = 0; i < n_vertices; i++) {
    float x, y, z;
    char comma;
    file >> x >> comma >> y >> comma >> z;
    textures.emplace_back(x, y, z);
  }

  file.close();

  return ParsedModel(vertices, normals, textures);
}

void GroupNode::addTransform(Transform *transform) {
  transforms.push_back(transform);
}

void GroupNode::addModel(Model *m) { models.push_back(m); }

void GroupNode::addSubNode(GroupNode *node) { sub_nodes.push_back(node); }

GroupNode::GroupNode(vector<GroupNode *> &_sub_nodes,
                     vector<Transform *> &_transforms, vector<Model *> &_models)
    : sub_nodes(_sub_nodes), transforms(_transforms), models(_models) {}

GroupNode::GroupNode() {}

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
