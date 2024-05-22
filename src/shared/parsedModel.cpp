#include "parsedModel.hpp"
#include <fstream>
#include <iostream>

using namespace std;

ParsedModel::ParsedModel(vector<Point> vertex, vector<Point> normals,
                         vector<Point> textures) {
  this->vertex = vertex;
  this->normals = normals;
  this->textures = textures;
}

ParsedModel::ParsedModel(string *file_name, bool has_textures) {
  vector<Point> vertices;
  vector<Point> normals;
  vector<Point> textures;

  ifstream file(*file_name);

  if (!file.is_open()) {
    cerr << "Error: file not found: " << *file_name << endl;
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
  if (has_textures)
    for (int i = 0; i < n_vertices; i++) {
      float x, y, z;
      char comma;
      file >> x >> comma >> y >> comma >> z;
      textures.emplace_back(x, y, z);
    }

  file.close();

  this->vertex = vertices;
  this->normals = normals;
  this->textures = textures;
}

vector<Point> ParsedModel::getVertex() { return vertex; }

vector<Point> ParsedModel::getNormals() { return normals; }

vector<Point> ParsedModel::getTextures() { return textures; }
