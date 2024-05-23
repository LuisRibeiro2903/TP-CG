#include "cgmath.hpp"
#include "parsedModel.hpp"
#include "point.hpp"
#include <math.h>

ParsedModel generateSphere(float radius, int slices, int stacks) {
  vector<Point> vertices;
  vector<Point> normals;
  vector<Point> textures;

  float alpha = 2 * M_PI / slices; // angle between slices
  float beta = M_PI / stacks;      // angle between stacks
  float texSliceStep = 1.0f / slices;
  float texStackStep = 1.0f / stacks;

  for (int stack = 0; stack < stacks; stack++) {
    float beta_now = M_PI / 2 - stack * beta;

    for (int slice = 0; slice < slices; slice++) {
      float alpha_now = slice * alpha;
      /*
      p1 --- p2
      | \    |
      |  \   |
      |   \  |
      |    \ |
      |     \|
      p3 --- p4
      */

      Point p1 =
          Point(radius * cos(beta_now) * sin(alpha_now), radius * sin(beta_now),
                radius * cos(beta_now) * cos(alpha_now));
      Point n1 = normalize2(
          p1); // Normal is the vector p1 - center normalized, and the center is
               // 0,0,0, so its the same as p1 normalized
      Point t1 = Point(texSliceStep * slice, 1 - (stack * texStackStep), 0);
      Point p2 = Point(radius * cos(beta_now) * sin(alpha_now + alpha),
                       radius * sin(beta_now),
                       radius * cos(beta_now) * cos(alpha_now + alpha));
      Point n2 = normalize2(p2);
      Point t2 = Point(texSliceStep * (slice + 1), 1 - (stack * texStackStep), 0);
      Point p3 = Point(radius * cos(beta_now - beta) * sin(alpha_now),
                       radius * sin(beta_now - beta),
                       radius * cos(beta_now - beta) * cos(alpha_now));
      Point n3 = normalize2(p3);
      Point t3 = Point(texSliceStep * slice, 1 - ((stack + 1) * texStackStep), 0);
      Point p4 = Point(radius * cos(beta_now - beta) * sin(alpha_now + alpha),
                       radius * sin(beta_now - beta),
                       radius * cos(beta_now - beta) * cos(alpha_now + alpha));
      Point n4 = normalize2(p4);
      Point t4 = Point(texSliceStep * (slice + 1),1 - ((stack + 1) * texStackStep), 0);

      // When stack is 0, we don't need to add 2 triangles, because p2 and p1
      // are the same point
      if (stack != stacks - 1) {
        vertices.push_back(p1);
        normals.push_back(n1);
        textures.push_back(t1);
        vertices.push_back(p3);
        normals.push_back(n3);
        textures.push_back(t3);
        vertices.push_back(p4);
        normals.push_back(n4);
        textures.push_back(t4);
      }

      // When stack is at stacks, we don't need to add 2 triangles, because p4
      // and p3 are the same point
      if (stack != 0) {
        vertices.push_back(p1);
        normals.push_back(n1);
        textures.push_back(t1);
        vertices.push_back(p4);
        normals.push_back(n4);
        textures.push_back(t4);
        vertices.push_back(p2);
        normals.push_back(n2);
        textures.push_back(t2);
      }
    }
  }

  return ParsedModel(vertices, normals, textures);
}
