#ifndef SCALE
#define SCALE

#include "transform.hpp"
#include "engine/frustum/AABox.hpp"
#include <GL/gl.h>

class Scale : public Transform {
private:
  float x, y, z;

public:
  Scale(float x, float y, float z);
  void applyTransform() override;
  void applyTransform(float *matrix) override;
  void applyTransformToAABox(AABox &box) override;
};

#endif
