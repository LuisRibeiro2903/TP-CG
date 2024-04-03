#ifndef SCALE
#define SCALE

#include "transform.hpp"

class Scale : public Transform {
private:
  float x, y, z;

public:
  Scale(float x, float y, float z);
  void applyTransform() const override;
};

#endif
