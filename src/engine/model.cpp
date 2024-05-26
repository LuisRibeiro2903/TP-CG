#include "model.hpp"
#include "point.hpp"
#include <GL/glew.h>
#include <IL/il.h>
#include <tuple>
#include <iostream>
#include <cstring>

using namespace std;

int loadTexture(string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,    GL_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
  

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}

vector<Point> Model::createNormalLineVector() {
  vector<Point> normal_lines;
  size_t size = model.size();
  for (int i = 0; i < size; i++)
  { 
    Point p = model[i];
    Point n = normals[i];
    normal_lines.push_back(p);
    normal_lines.emplace_back(p.x() + n.x(), p.y() + n.y(), p.z() + n.z());
  }
  return normal_lines;
}

void Model::setBoundingBox() {
  Point min = model[0];
  Point max = model[0];
  for (Point p : model) {
    if (p.x() < min.x())
      min.setX(p.x());
    if (p.y() < min.y())
      min.setY(p.y());
    if (p.z() < min.z())
      min.setZ(p.z());

    if (p.x() > max.x())
      max.setX(p.x());
    if (p.y() > max.y())
      max.setY(p.y());
    if (p.z() > max.z())
      max.setZ(p.z());
  }

  this->box = AABox(min, max);

}

void Model::createVBOS() {
  GLuint vboModel, vboNormals, vboTexture, vboNormalLines;
  glGenBuffers(1, &vboModel);
  glBindBuffer(GL_ARRAY_BUFFER, vboModel);
  vector<float> model_tmp;
  for (Point p : model) {
    model_tmp.push_back(p.x());
    model_tmp.push_back(p.y());
    model_tmp.push_back(p.z());
  }
  glBufferData(GL_ARRAY_BUFFER, model_tmp.size() * sizeof(float),
               model_tmp.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &vboNormals);
  glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
  vector<float> normals_tmp;
  for (Point p : normals) {
    normals_tmp.push_back(p.x());
    normals_tmp.push_back(p.y());
    normals_tmp.push_back(p.z());
  }
  glBufferData(GL_ARRAY_BUFFER, normals_tmp.size() * sizeof(float),
               normals_tmp.data(), GL_STATIC_DRAW);



  glGenBuffers(1, &vboNormalLines);
  glBindBuffer(GL_ARRAY_BUFFER, vboNormalLines);
  vector<Point> normal_lines = createNormalLineVector();
  vector<float> normal_lines_tmp;
  for (Point p : normal_lines) {
    normal_lines_tmp.push_back(p.x());
    normal_lines_tmp.push_back(p.y());
    normal_lines_tmp.push_back(p.z());
  }
  glBufferData(GL_ARRAY_BUFFER, normal_lines_tmp.size() * sizeof(float),
               normal_lines_tmp.data(), GL_STATIC_DRAW);

  if (texPath != nullptr)
    texID = loadTexture(*texPath);
  else
    texID = -1;

  if (texID != -1) {
    glGenBuffers(1, &vboTexture);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
    vector<float> texture_tmp;
    for (Point p : texture) {
      texture_tmp.push_back(p.x());
      texture_tmp.push_back(p.y());
    }
    glBufferData(GL_ARRAY_BUFFER, texture_tmp.size() * sizeof(float),
                 texture_tmp.data(), GL_STATIC_DRAW);

    //We also set the bounding box
  }
  this->setBoundingBox();

  vbos = make_tuple(vboModel, vboNormals, vboTexture, vboNormalLines);
}

Model::Model(vector<Point> _model, vector<Point> _normals,
             vector<Point> _texture, Color *_color, string * texPath, string * _name)
    : model(_model), normals(_normals), texture(_texture), color(*_color), texPath(texPath), name(_name) {}



void Model::drawAABox() {
  box.draw();
}

void Model::resetAABox() {
  box.reset();
}

bool Model::draw(bool debugNormals, char * nameF) {
  GLuint vboModel, vboNormals, vboTexture, vboNormalLines;
  vboModel = get<0>(vbos);
  vboNormals = get<1>(vbos);
  vboNormalLines = get<3>(vbos);
  if (texID != -1)
    vboTexture = get<2>(vbos);
  bool fixed = false;
  char tmpName[100];
  strcpy(tmpName, this->name->c_str());

  if (nameF != nullptr && name != nullptr && !strcmp(tmpName, nameF)) {
    fixed = true;
  }

  if (debugNormals){
    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormalLines);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_LINES, 0, model.size() * 2);
    glEnable(GL_LIGHTING);
  }

  if (texID != -1) {
    glBindTexture(GL_TEXTURE_2D, texID);
  }

  glMaterialfv(GL_FRONT, GL_DIFFUSE, color.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, color.specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, color.ambient);
  glMaterialfv(GL_FRONT, GL_EMISSION, color.emissive);
  glMateriali(GL_FRONT, GL_SHININESS, color.shininess);

  glBindBuffer(GL_ARRAY_BUFFER, vboModel);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  
  glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
  glNormalPointer(GL_FLOAT, 0, 0);

  if (texID != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
  }


  glDrawArrays(GL_TRIANGLES, 0, model.size());

  if (texID != -1) {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  return fixed;

}

void Model::updateAABox(float * matrix) {
  box.transform(matrix);
}

Model::~Model() {
  auto [vboModel, vboNormals, vboTexture, vboNormalLines] = vbos;
  glDeleteBuffers(1, &vboModel);
  glDeleteBuffers(1, &vboNormals);
  if (texID != -1)
    glDeleteBuffers(1, &vboTexture);
  glDeleteBuffers(1, &vboNormalLines);
}
