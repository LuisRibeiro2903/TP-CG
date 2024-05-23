#ifndef TRANSLATE
#define TRANSLATE

#include "engine/transform/transform.hpp"
#include "engine/frustum/AABox.hpp"
#include <GL/gl.h>

class Translate : public Transform {
private:
  float x, y, z;

public:
  Translate(float x, float y, float z);
  void applyTransform() override;
  void applyTransform(float *matrix) override;
  void applyTransformToAABox(AABox &box) override;
};

#endif
