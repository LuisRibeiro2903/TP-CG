#include "model.hpp"
#include "point.hpp"
#include <GL/glew.h>
#include <IL/il.h>
#include <tuple>

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
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
  glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}

void Model::createVBOS() {
  GLuint vboModel, vboNormals, vboTexture;
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
  }

  vbos = make_tuple(vboModel, vboNormals, vboTexture);
}

Model::Model(vector<Point> _model, vector<Point> _normals,
             vector<Point> _texture, Color *_color, string * texPath)
    : model(_model), normals(_normals), texture(_texture), color(*_color), texPath(texPath) {}


void Model::draw() {
  GLuint vboModel, vboNormals, vboTexture;
  vboModel = get<0>(vbos);
  vboNormals = get<1>(vbos);
  if (texID != -1)
    vboTexture = get<2>(vbos);

  if (texID != -1) {
    glBindTexture(GL_TEXTURE_2D, texID);
  }

  /* glMaterialfv(GL_FRONT, GL_DIFFUSE, color.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, color.specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, color.ambient);
  glMaterialfv(GL_FRONT, GL_EMISSION, color.emissive);
  glMateriali(GL_FRONT, GL_SHININESS, color.shininess);  */

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

}

Model::~Model() {
  auto [vboModel, vboNormals, vboTexture] = vbos;
  glDeleteBuffers(1, &vboModel);
  glDeleteBuffers(1, &vboNormals);
  if (texID != -1)
    glDeleteBuffers(1, &vboTexture);
}
