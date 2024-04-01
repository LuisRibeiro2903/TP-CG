#include "model.hpp"
#include "point.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

class Model {
  string file_path;

  vector<vector<Point>> parse3dFile(vector<string> models) {
    vector<vector<Point>> all_vertices;

    for (string model : models) {
      vector<Point> vertices;
      ifstream file(file_path);

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

public:
  void drawModel() {
    vector<Point> vertices = parse3dFile(vector<string> models);
  }
};
