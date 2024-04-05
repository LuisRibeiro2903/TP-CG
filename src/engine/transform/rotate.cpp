#include "engine/transform/rotate.hpp"
#include <GL/gl.h>

Rotate::Rotate(float angle, float x, float y, float z)
    : angle(angle), x(x), y(y), z(z) {}

void Rotate::applyTransform() const { glRotatef(angle, x, y, z); }
