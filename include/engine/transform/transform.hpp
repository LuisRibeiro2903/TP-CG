// abstract class that defines a transformation
#ifndef TRANSFORM
#define TRANSFORM

#include "engine/frustum/AABox.hpp"


using namespace std;

class Transform {
public:
  virtual void applyTransform() = 0;
  virtual void applyTransform(float *matrix) = 0;
};

#endif
