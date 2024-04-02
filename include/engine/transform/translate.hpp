#include "transform.hpp"

class Translate : public Transform {
private:
  float x, y, z;

public:
  Translate(float x, float y, float z);
  void applyTransform() const override;
};
