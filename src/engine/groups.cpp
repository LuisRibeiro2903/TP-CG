#include "groups.hpp"
#include "engine/transform/transform.hpp"
#include <engine/transform/transform.hpp>
#include "parsedModel.hpp"
#include <engine/color.hpp>
#include "parser.hpp"
#include "point.hpp"
#include <fstream>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

ParsedModel parse3dFile(string * model) {
  vector<Point> vertices;
  vector<Point> normals;

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
  for(int i = 0; i < n_vertices; i++) {
    float x, y, z;
    char comma;
    file >> x >> comma >> y >> comma >> z;
    normals.emplace_back(x, y, z);
  }

  file.close();

  return ParsedModel(vertices, normals, {});
}


void GroupNode::addTransform(Transform *transform) {
  transforms.push_back(transform);
}

void GroupNode::addModel(string *model) { models.push_back(model); }

void GroupNode::addSubNode(GroupNode *node) { sub_nodes.push_back(node); }

void GroupNode::addColor(vector<Color *> _color) {
  color = _color;
}

GroupNode::GroupNode(vector<GroupNode *> &_sub_nodes,
                     vector<Transform *> &_transforms,
                     vector<string *> &_models,
                    vector<Color *> _color)
    : sub_nodes(_sub_nodes), transforms(_transforms), models(_models), color(_color){}


GroupNode::GroupNode()  {  }

void GroupNode::drawModels(bool debugNormals) {

  for (int i = 0; i < n_models; i++) {
    if (debugNormals){
      glDisable(GL_LIGHTING);
      glColor3f(1, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, normal_line_vbos[i]);
      glVertexPointer(3, GL_FLOAT, 0, 0);
      glDrawArrays(GL_LINES, 0, model_sizes[i] * 2);
      glEnable(GL_LIGHTING);

    }
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[i]->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[i]->specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[i]->ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, color[i]->emissive);
    glMaterialf(GL_FRONT, GL_SHININESS, color[i]->shininess);
    glBindBuffer(GL_ARRAY_BUFFER, model_vbos[i]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, normal_vbos[i]);
    glNormalPointer(GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, model_sizes[i]);
  }
  
}

vector<Point> createNormalLineVector(vector<Point> normals, vector<Point> vertices, int n_vertices) {
  vector<Point> normal_lines;
  for (int i = 0; i < n_vertices; i++) {
    Point p = vertices[i];
    Point n = normals[i];
    normal_lines.push_back(p);
    normal_lines.emplace_back(p.x() + n.x(), p.y() + n.y(), p.z() + n.z());
  }
  return normal_lines;
}

void GroupNode::createVBOs() {

  if (models.size() == 0) {
    n_models = 0;
    return;
  }
  n_models = models.size();
  model_vbos = (GLuint *)malloc(n_models * sizeof(GLuint));
  normal_vbos = (GLuint *)malloc(n_models * sizeof(GLuint));
  normal_line_vbos = (GLuint *)malloc(n_models * sizeof(GLuint));
  model_sizes = (size_t *)malloc(n_models * sizeof(size_t));
  glGenBuffers(n_models, model_vbos);
  glGenBuffers(n_models, normal_vbos);
  glGenBuffers(n_models, normal_line_vbos);

  for(int i = 0; i < n_models; i++) {
    ParsedModel model = parse3dFile(models[i]);
    vector<Point> position = model.getVertex();
    model_sizes[i] = position.size();
    glBindBuffer(GL_ARRAY_BUFFER, model_vbos[i]);
    glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(Point), &(position[0]), GL_STATIC_DRAW);
    vector<Point> normal = model.getNormals();
    glBindBuffer(GL_ARRAY_BUFFER, normal_vbos[i]);
    glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(Point), &(normal[0]), GL_STATIC_DRAW);
    vector<Point> normal_lines = createNormalLineVector(normal, position, position.size());
    glBindBuffer(GL_ARRAY_BUFFER, normal_line_vbos[i]);
    glBufferData(GL_ARRAY_BUFFER, normal_lines.size() * sizeof(Point), &(normal_lines[0]), GL_STATIC_DRAW);
  }
}

void GroupNode::initializeVBOs() {
  this->createVBOs();
  for (GroupNode * node : sub_nodes) {
    node->initializeVBOs();
  }
}

void GroupNode::applyColor() {
  
}

void GroupNode::draw(bool debugNormals) {
  glPushMatrix();


  for (Transform *t : transforms) {
    t->applyTransform();
  }


  this->drawModels(debugNormals);

  for (GroupNode * node : sub_nodes) {
    node->draw(debugNormals);
  }

  glPopMatrix();
}
