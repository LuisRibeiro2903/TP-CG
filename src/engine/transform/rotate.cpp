#include "engine/transform/rotate.hpp"

Rotate::Rotate(float angleOrTime, float x, float y, float z, bool isTime) 
    : angleOrTime(angleOrTime), x(x), y(y), z(z) , isTime(isTime) {}

void Rotate::applyTransform()  { 

    float angle = isTime ? ((float)glutGet(GLUT_ELAPSED_TIME) * 360.0f / 1000) / angleOrTime : angleOrTime;
    glRotatef(angle, x, y, z); 

}

void Rotate::applyTransformToAABox(AABox &box) {
    
}

void Rotate::applyTransform(float *matrix) {
    
}
