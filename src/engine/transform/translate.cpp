#include "engine/transform/translate.hpp"

Translate::Translate(float x, float y, float z) : x(x), y(y), z(z) {}

void Translate::applyTransform() { glTranslatef(x, y, z); }

void Translate::applyTransform(GLfloat *matrix)
{
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] += z;
}

void Translate::applyTransformToAABox(AABox &box)
{
    box.translate(x, y, z);
}