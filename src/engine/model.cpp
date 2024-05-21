#include "model.hpp"
#include "point.hpp"
#include <GL/glew.h>
#include <tuple>

using namespace std;

tuple<GLuint, GLuint, GLuint> Model::createVBOS() {
  GLuint vboModel, vboNormals, vboTexture;
  glGenBuffers(1, &vboModel);
  glBindBuffer(GL_ARRAY_BUFFER, vboModel);
  glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(Point), model.data(),
               GL_STATIC_DRAW);

  glGenBuffers(1, &vboNormals);
  glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Point), normals.data(),
               GL_STATIC_DRAW);

  if (texture.size() > 0) {
    glGenBuffers(1, &vboTexture);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
    glBufferData(GL_ARRAY_BUFFER, texture.size() * sizeof(Point),
                 texture.data(), GL_STATIC_DRAW);
  }

  return make_tuple(vboModel, vboNormals, vboTexture);
}

Model::Model(vector<Point> *_model, vector<Point> *_normals,
             vector<Point> *_texture, Color *_color)
    : model(*_model), normals(*_normals), texture(*_texture), color(*_color) {
  vbos = createVBOS();
}

// TODO: Falta a parte em que se aplica a textura em si acredito eu
void Model::draw() {
  auto [vboModel, vboNormals, vboTexture] = vbos;

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vboModel);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void *)0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void *)0);

  if (texture.size() > 0) {
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void *)0);
  }

  glMaterialfv(GL_FRONT, GL_DIFFUSE, color.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, color.specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, color.ambient);
  glMaterialfv(GL_FRONT, GL_EMISSION, color.emissive);
  glMateriali(GL_FRONT, GL_SHININESS, color.shininess);

  glDrawArrays(GL_TRIANGLES, 0, model.size());

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

Model::~Model() {
  auto [vboModel, vboNormals, vboTexture] = vbos;
  glDeleteBuffers(1, &vboModel);
  glDeleteBuffers(1, &vboNormals);
  if (texture.size() > 0)
    glDeleteBuffers(1, &vboTexture);
}
