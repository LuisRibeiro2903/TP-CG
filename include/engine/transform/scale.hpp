#ifndef SCALE
#define SCALE

#include "transform.hpp"
#include <GL/gl.h>

class Scale : public Transform {
private:
  float x, y, z;

public:
  Scale(float x, float y, float z);
  void applyTransform() const override;
};

#endif
