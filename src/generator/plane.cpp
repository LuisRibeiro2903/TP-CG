#include "point.hpp"
#include "parsedModel.hpp"
#include <vector>

using namespace std;

ParsedModel generatePlane(float length, int divisions)
{
  vector<Point> vertices;
  vector<Point> normals;

  float step = length / divisions;

  float halfLength = length / 2.0f;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            
            // Calculate vertices for the current square
            float x0 = -halfLength + j * step;
            float z0 = -halfLength + i * step;
            float x1 = x0 + step;
            float z1 = z0 + step;

            // Add vertices for the two triangles in the square
            vertices.emplace_back(x0, 0.0f, z0);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x1, 0.0f, z1);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x1, 0.0f, z0);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x0, 0.0f, z0);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x0, 0.0f, z1);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x1, 0.0f, z1);
            normals.emplace_back(0, 1, 0);
        }
    }

  return ParsedModel(vertices, normals, {});
}
