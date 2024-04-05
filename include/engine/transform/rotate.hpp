#ifndef ROTATE
#define ROTATE

#include "transform.hpp"

class Rotate : public Transform {
private:
  float angle, x, y, z;

public:
  Rotate(float angle, float x, float y, float z);
  void applyTransform() const override;
};

#endif
