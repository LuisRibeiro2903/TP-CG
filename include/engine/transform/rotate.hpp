#ifndef ROTATE
#define ROTATE

#include "transform.hpp"
#include <GL/glut.h>
#include <GL/gl.h>

class Rotate : public Transform {
private:
  float angleOrTime, x, y, z;
  bool isTime;

public:
  Rotate(float angleOrTime, float x, float y, float z, bool isTime);
  void applyTransform() override;
};

#endif
