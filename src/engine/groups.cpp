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

vector<vector<Point>> parse3dFiles(vector<string> models) {
  vector<vector<Point>> all_vertices;

  for (const string model : models) {
    vector<Point> vertices;
    ifstream file(model);

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
      vertices.push_back(Point(x, y, z));
    }

    all_vertices.push_back(vertices);
    file.close();
  }

  return all_vertices;
}

void drawModels(const vector<vector<Point>> &model_vertices) {
  for (const vector<Point> &model : model_vertices) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(Point), model.data(),
                 GL_STATIC_DRAW);

    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, model.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
  }
}

GroupNode::GroupNode(vector<GroupNode *> _sub_nodes,
                     vector<Transform *> _transforms, vector<string> _models)
    : sub_nodes(_sub_nodes), transforms(_transforms), models(_models) {}

void GroupNode::drawNodes() {
  glPushMatrix();

  for (const Transform *t : transforms) {
    t->applyTransform();
  }

  drawModels(parse3dFiles(models));

  glPopMatrix();
}
