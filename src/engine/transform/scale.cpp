#include "engine/transform/scale.hpp"

Scale::Scale(float x, float y, float z) : x(x), y(y), z(z) {}

void Scale::applyTransform() const { glScalef(x, y, z); }
