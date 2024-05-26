#include "groups.hpp"
#include "engine/transform/transform.hpp"
#include "parsedModel.hpp"
#include "cgmath.hpp"
#include "parser.hpp"
#include <engine/color.hpp>
#include <engine/transform/transform.hpp>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

void GroupNode::addTransform(Transform *transform) {
  transforms.push_back(transform);
}

void GroupNode::addModel(Model *m) { models.push_back(m); }

void GroupNode::addSubNode(GroupNode *node) { sub_nodes.push_back(node); }

GroupNode::GroupNode(vector<GroupNode *> &_sub_nodes,
                     vector<Transform *> &_transforms, vector<Model *> &_models)
    : sub_nodes(_sub_nodes), transforms(_transforms), models(_models) {
    }

GroupNode::GroupNode() {
  
}

void GroupNode::initVBOs() {
  for (Model *m : models) {
    m->createVBOS();
  }

  for (GroupNode *node : sub_nodes) {
    node->initVBOs();
  }
}

void GroupNode::resetAABox() {
  for (Model *m : models) {
    m->resetAABox();
  }

  for (GroupNode *node : sub_nodes) {
    node->resetAABox();
  }
}


void GroupNode::buildTransformationMatrix(float * matrix, float * matrixToAABox) {


  //Apply the transformations to the matrix
  for (Transform *t : transforms) {
    t->applyTransform(matrix);
  }

  float matrixT[16];

  float matrixToAABox2[16] = {
    matrixToAABox[0], matrixToAABox[1], matrixToAABox[2], matrixToAABox[3],
    matrixToAABox[4], matrixToAABox[5], matrixToAABox[6], matrixToAABox[7],
    matrixToAABox[8], matrixToAABox[9], matrixToAABox[10], matrixToAABox[11],
    matrixToAABox[12], matrixToAABox[13], matrixToAABox[14], matrixToAABox[15]
  };

  multiply(matrixToAABox2, matrix, matrixToAABox);


  for (Model * m : models)
    m->updateAABox(matrixToAABox);

  //Transpose the matrix
  transpose(matrix, matrixT);

  memcpy(matrix, matrixT, sizeof(matrixT));

}

int GroupNode::totalModels() {
  int total = 0;
  for (Model *m : models) {
    total++;
  }

  for (GroupNode *node : sub_nodes) {
    total += node->totalModels();
  }

  return total;

}

void GroupNode::drawAABox() {
  for (Model *m : models) {
    m->drawAABox();
  }

  for (GroupNode *node : sub_nodes) {
    node->drawAABox();
  }
}


void GroupNode::draw(bool debugNormals, bool frustumOn, int * modelosDesenhados, FrustumG *frustum, float * matrixToAABox) {
  glPushMatrix();


  //Initialize the identity matrix
  float matrix[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };

  buildTransformationMatrix(matrix, matrixToAABox);


  glMultMatrixf(matrix);


  for (Model *m : models) {
    AABox box = m->getAABox();
    if (!frustumOn || (frustum->boxInFrustum(box) != FrustumG::OUTSIDE)) {
      m->draw(debugNormals);
      (*modelosDesenhados)++;
    }
  }

  for (GroupNode *node : sub_nodes) {
    float matrixToAABox2[16];
    memcpy(matrixToAABox2, matrixToAABox, sizeof(matrixToAABox2));
    node->draw(debugNormals, frustumOn, modelosDesenhados, frustum, matrixToAABox2);
  }

  glPopMatrix();
}
