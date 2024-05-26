#include "engine/transform/rotate.hpp"
#include "cgmath.hpp"

#include <cmath>

Rotate::Rotate(float angleOrTime, float x, float y, float z, bool isTime) 
    : angleOrTime(angleOrTime), x(x), y(y), z(z) , isTime(isTime) {}

void Rotate::applyTransform()  { 

    float angle = isTime ? ((float)glutGet(GLUT_ELAPSED_TIME) * 360.0f / 1000) / angleOrTime : angleOrTime;
    glRotatef(angle, x, y, z); 

}



void Rotate::applyTransform(float *matrix) {
    
    float angle = isTime ? ((float)glutGet(GLUT_ELAPSED_TIME) * 360.0f / 1000) / angleOrTime : angleOrTime;

    float matrix_copy[16];
    for (int i = 0; i < 16; i++) {
        matrix_copy[i] = matrix[i];
    }
    angle = angle * M_PI / 180;    

    float rotation_matrix[16] = {
        x*x + (1 - x*x) * cos(angle), x*y*(1 - cos(angle)) - z*sin(angle), x*z*(1 - cos(angle)) + y*sin(angle), 0,
        y*x*(1 - cos(angle)) + z*sin(angle), y*y + (1 - y*y) * cos(angle), y*z*(1 - cos(angle)) - x*sin(angle), 0,
        z*x*(1 - cos(angle)) - y*sin(angle), z*y*(1 - cos(angle)) + x*sin(angle), z*z + (1 - z*z) * cos(angle), 0,
        0                                  , 0                                  , 0                           , 1
    };


    multiply(matrix_copy, rotation_matrix, matrix);


}
