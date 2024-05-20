#include "parsedModel.hpp"
#include "point.hpp"
#include <vector>

void generatePlanesXZ(float dimension, int divisions, vector<Point> &vertices,
                      vector<Point> &normals, vector<Point> &textures) {
  float step = dimension / divisions;
  float step_tex = 1.0f / divisions;
  float halfDimension = dimension / 2.0f;

  for (int i = 0; i < divisions; i++) {
    for (int j = 0; j < divisions; j++) {

      // Calculate vertices for the current square
      float x0 = -halfDimension + j * step;
      float z0 = -halfDimension + i * step;
      float x1 = x0 + step;
      float z1 = z0 + step;

      // Vertices for Top Face
      float x0_text = j * step_tex;
      float y0_text = i * step_tex;
      float x1_text = x0_text + step_tex;
      float y1_text = y0_text + step_tex;

      // Lower triangle Top Face - T1
      vertices.emplace_back(x0, halfDimension, z0);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x0_text, y1_text, 0);
      vertices.emplace_back(x1, halfDimension, z1);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x1, halfDimension, z0);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x1_text, y1_text, 0);

      // Upper triangle Top Face - T2
      vertices.emplace_back(x0, halfDimension, z1);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x0_text, y0_text, 0);
      vertices.emplace_back(x1, halfDimension, z1);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x0, halfDimension, z0);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x0_text, y1_text, 0);

      // Lower triangle Bottom Face - T3
      vertices.emplace_back(x0, -halfDimension, z1);
      normals.emplace_back(0, -1, 0);
      textures.emplace_back(x0_text, y1_text, 0);
      vertices.emplace_back(x1, -halfDimension, z0);
      normals.emplace_back(0, -1, 0);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x1, -halfDimension, z1);
      normals.emplace_back(0, -1, 0);
      textures.emplace_back(x1_text, y1_text, 0);

      // Upper triangle Bottom Face - T4
      vertices.emplace_back(x0, -halfDimension, z0);
      normals.emplace_back(0, -1, 0);
      textures.emplace_back(x0_text, y0_text, 0);
      vertices.emplace_back(x1, -halfDimension, z0);
      normals.emplace_back(0, -1, 0);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x0, -halfDimension, z1);
      normals.emplace_back(0, -1, 0);
      textures.emplace_back(x0_text, y0_text, 0);
    }
  }
}

void generatePlanesXY(float dimension, int divisions, vector<Point> &vertices,
                      vector<Point> &normals, vector<Point> &textures) {
  float step = dimension / divisions;
  float step_tex = 1.0f / divisions;
  float halfDimension = dimension / 2.0f;

  for (int i = 0; i < divisions; i++) {
    for (int j = 0; j < divisions; j++) {

      // Calculate vertices for the current square
      float x0 = -halfDimension + j * step;
      float y0 = -halfDimension + i * step;
      float x1 = x0 + step;
      float y1 = y0 + step;

      // Vertices for Front Face
      float x0_text = j * step_tex;
      float y0_text = i * step_tex;
      float x1_text = x0_text + step_tex;
      float y1_text = y0_text + step_tex;

      // Front Upper triangle - T5
      vertices.emplace_back(x1, y0, halfDimension);
      normals.emplace_back(0, 0, 1);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x1, y1, halfDimension);
      normals.emplace_back(0, 0, 1);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x0, y1, halfDimension);
      normals.emplace_back(0, 0, 1);
      textures.emplace_back(x0_text, y1_text, 0);

      // Front Lower triangle - T6
      vertices.emplace_back(x0, y0, halfDimension);
      normals.emplace_back(0, 0, 1);
      textures.emplace_back(x0_text, y0_text, 0);
      vertices.emplace_back(x1, y0, halfDimension);
      normals.emplace_back(0, 0, 1);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x0, y1, halfDimension);
      normals.emplace_back(0, 0, 1);
      textures.emplace_back(x0_text, y1_text, 0);

      // Back Upper triangle - T8
      vertices.emplace_back(x1, y1, -halfDimension);
      normals.emplace_back(0, 0, -1);
      textures.emplace_back(x0_text, y0_text, 0);
      vertices.emplace_back(x0, y0, -halfDimension);
      normals.emplace_back(0, 0, -1);
      textures.emplace_back(x0_text, y0_text, 0);
      vertices.emplace_back(x0, y1, -halfDimension);
      normals.emplace_back(0, 0, -1);
      textures.emplace_back(x0_text, y0_text, 0);

      // Back Lower triangle - T7
      vertices.emplace_back(x0, y0, -halfDimension);
      normals.emplace_back(0, 0, -1);
      textures.emplace_back(x0_text, y1_text, 0);
      vertices.emplace_back(x1, y1, -halfDimension);
      normals.emplace_back(0, 0, -1);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(x1, y0, -halfDimension);
      normals.emplace_back(0, 0, -1);
      textures.emplace_back(x1_text, y1_text, 0);
    }
  }
}

void generatePlanesYZ(float dimension, int divisions, vector<Point> &vertices,
                      vector<Point> &normals, vector<Point> &textures) {
  float step = dimension / divisions;
  float step_tex = 1.0f / divisions;
  float halfDimension = dimension / 2.0f;

  for (int i = 0; i < divisions; i++) {
    for (int j = 0; j < divisions; j++) {

      // Calculate vertices for the current square
      float y0 = -halfDimension + j * step;
      float z0 = -halfDimension + i * step;
      float y1 = y0 + step;
      float z1 = z0 + step;

      // Vertices for Right Face
      float x0_text = j * step_tex;
      float y0_text = i * step_tex;
      float x1_text = x0_text + step_tex;
      float y1_text = y0_text + step_tex;

      // Upper triangle Right Face - T9
      vertices.emplace_back(halfDimension, y0, z0);
      normals.emplace_back(1, 0, 0);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(halfDimension, y1, z0);
      normals.emplace_back(1, 0, 0);
      textures.emplace_back(x1_text, y1_text, 0);
      vertices.emplace_back(halfDimension, y1, z1);
      normals.emplace_back(1, 0, 0);
      textures.emplace_back();
      textures.emplace_back(x0_text, y1_text, 0);

      // Lower triangle Right Face - T10
      vertices.emplace_back(halfDimension, y0, z0);
      normals.emplace_back(1, 0, 0);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(halfDimension, y1, z1);
      normals.emplace_back(1, 0, 0);
      textures.emplace_back(x0_text, y1_text, 0);
      vertices.emplace_back(halfDimension, y0, z1);
      normals.emplace_back(1, 0, 0);
      textures.emplace_back(x0_text, y0_text, 0);

      // Lower triangle Left Face
      vertices.emplace_back(-halfDimension, y0, z0);
      normals.emplace_back(-1, 0, 0);
      textures.emplace_back(x1_text, y0_text, 0);
      vertices.emplace_back(-halfDimension, y0, z1);
      normals.emplace_back(-1, 0, 0);
      textures.emplace_back(x0_text, y0_text, 0);
      vertices.emplace_back(-halfDimension, y1, z0);
      normals.emplace_back(-1, 0, 0);
      textures.emplace_back(x1_text, y1_text, 0);

      // Upper triangle Left Face
      vertices.emplace_back(-halfDimension, y1, z1);
      normals.emplace_back(-1, 0, 0);
      textures.emplace_back(x0_text, y1_text, 0);
      vertices.emplace_back(-halfDimension, y1, z0);
      normals.emplace_back(-1, 0, 0);
      textures.emplace_back(x1_text, y1_text, 0);
      vertices.emplace_back(-halfDimension, y0, z1);
      normals.emplace_back(-1, 0, 0);
      textures.emplace_back(x0_text, y0_text, 0);
    }
  }
}

ParsedModel generateBox(float dimension, int divisions) {
  std::vector<Point> box;
  std::vector<Point> normals;
  vector<Point> textures;

  // Topo e base
  generatePlanesXZ(dimension, divisions, box, normals, textures);
  // Lados
  generatePlanesYZ(dimension, divisions, box, normals, textures);
  // Frente e trás
  generatePlanesXY(dimension, divisions, box, normals, textures);

  return ParsedModel(box, normals, textures);
}
