#include "parsedModel.hpp"
#include "point.hpp"
#include <vector>

using std::vector;

ParsedModel generatePlane(float length, int divisions) {
  vector<Point> vertices;
  vector<Point> normals;
  vector<Point> textures;

  float step = length / divisions;
  float step_tex = 1.0f / divisions;
  float halfLength = length / 2.0f;

  for (int i = 0; i < divisions; i++) {
    for (int j = 0; j < divisions; j++) {

      // Calculate vertices for the current square
      float x0 = -halfLength + j * step;
      float z0 = -halfLength + i * step;
      float x1 = x0 + step;
      float z1 = z0 + step;

      // Vex vertices
      float x0_tex = j * step_tex;
      float y0_tex = i * step_tex;
      float x1_tex = x0_tex + step_tex;
      float y1_tex = y0_tex + step_tex;

      // Add vertices for the two triangles in the square
      vertices.emplace_back(x0, 0.0f, z0);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x0_tex, y0_tex, 0);
      vertices.emplace_back(x1, 0.0f, z1);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x1_tex, y1_tex, 0);
      vertices.emplace_back(x1, 0.0f, z0);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x1_tex, y0_tex, 0);
      vertices.emplace_back(x0, 0.0f, z0);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x0_tex, y0_tex, 0);
      vertices.emplace_back(x0, 0.0f, z1);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x0_tex, y1_tex, 0);
      vertices.emplace_back(x1, 0.0f, z1);
      normals.emplace_back(0, 1, 0);
      textures.emplace_back(x1_tex, y1_tex, 0);
    }
  }

  return ParsedModel(vertices, normals, textures);
}
