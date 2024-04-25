#ifndef TRANSLATE
#define TRANSLATE

#include "engine/transform/transform.hpp"
#include <GL/gl.h>

class Translate : public Transform {
private:
  float x, y, z;

public:
  Translate(float x, float y, float z);
  void applyTransform() override;
};

#endif
