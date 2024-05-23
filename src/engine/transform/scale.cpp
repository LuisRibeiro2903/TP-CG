#include "engine/transform/scale.hpp"

Scale::Scale(float x, float y, float z) : x(x), y(y), z(z) {}

void Scale::applyTransform() { glScalef(x, y, z); }

void Scale::applyTransformToAABox(AABox &box)
{
    box.scale(x, y, z);
}

void Scale::applyTransform(float *matrix)
{

}
