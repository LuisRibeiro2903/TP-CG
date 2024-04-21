#include "engine/transform/translate.hpp"

Translate::Translate(float x, float y, float z) : x(x), y(y), z(z) {}

void Translate::applyTransform() const { glTranslatef(x, y, z); }
