#include "groups.hpp"
#include "engine/transform/transform.hpp"
#include "parser.hpp"
#include "point.hpp"
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

vector<Point> parse3dFile(string * model) {
  vector<Point> vertices;

  ifstream file(*model);

  if (!file.is_open()) {
    cerr << "Error: file not found" << endl;
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

  file.close();

  return vertices;
}


void GroupNode::addTransform(Transform *transform) {
  transforms.push_back(transform);
}

void GroupNode::addModel(string *model) { models.push_back(model); }

void GroupNode::addSubNode(GroupNode *node) { sub_nodes.push_back(node); }

void GroupNode::setColor(float r, float g, float b) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

GroupNode::GroupNode(vector<GroupNode *> &_sub_nodes,
                     vector<Transform *> &_transforms,
                     vector<string *> &_models,
                     array<float, 3> &_color)
    : sub_nodes(_sub_nodes), transforms(_transforms), models(_models), color(_color){}


GroupNode::GroupNode() : color{{1.0f, 1.0f, 1.0f}} {}

void GroupNode::drawModels() {

  for (int i = 0; i < n_models; i++) {
    glBindBuffer(GL_ARRAY_BUFFER, model_vbos[i]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, model_sizes[i]);
  }
  
}

void GroupNode::createVBOs() {

  if (models.size() == 0) {
    n_models = 0;
    return;
  }
  n_models = models.size();
  model_vbos = (GLuint *)malloc(n_models * sizeof(GLuint));
  model_sizes = (size_t *)malloc(n_models * sizeof(size_t));
  glGenBuffers(n_models, model_vbos);

  for(int i = 0; i < n_models; i++) {
    vector<Point> position = parse3dFile(models[i]);
    model_sizes[i] = position.size();
    glBindBuffer(GL_ARRAY_BUFFER, model_vbos[i]);
    glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(Point), &(position[0]), GL_STATIC_DRAW);
  }
}

void GroupNode::initializeVBOs() {
  this->createVBOs();
  for (GroupNode * node : sub_nodes) {
    node->initializeVBOs();
  }
}

void GroupNode::draw() {
  glPushMatrix();

  glColor3f(1.0f, 1.0f, 1.0f);

  for (Transform *t : transforms) {
    t->applyTransform();
  }

  glColor3f(color[0], color[1], color[2]);

  this->drawModels();

  for (GroupNode * node : sub_nodes) {
    node->draw();
  }

  glPopMatrix();
}
