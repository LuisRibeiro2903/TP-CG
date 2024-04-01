#include "parser.hpp"
#include "point.hpp"
#include <iostream>
#include <model.hpp>
#include <transform.hpp>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

class GroupNode {
  vector<GroupNode> sub_nodes;
  vector<Transform> transforms;
  vector<string> models;

  vector<vector<Point>> parse3dFiles(vector<string> models) {
    vector<vector<Point>> all_vertices;

    for (string model : models) {
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

  void drawModels(vector<vector<Point>> model_vertices) {
    // stuff
    // morestuff
  }

public:
  GroupNode(std::vector<GroupNode> sub_nodes, std::vector<Transform> transforms,
            std::vector<Model> models)
      : sub_nodes(std::move(sub_nodes)), transforms(std::move(transforms)),
        std::move(models)) {}

  void drawNodes() {
    glPushMatrix();

    for (Transform t : transforms) {
      t.applyTransform();
    }

    drawModels(parse3dFiles(models));

    glPopMatrix();
  }
};
