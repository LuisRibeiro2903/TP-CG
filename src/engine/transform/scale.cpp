#include "engine/transform/scale.hpp"
#include "cgmath.hpp"

Scale::Scale(float x, float y, float z) : x(x), y(y), z(z) {}

void Scale::applyTransform() { glScalef(x, y, z); }


void Scale::applyTransform(float *matrix)
{
    float matrix_copy[16];
    for (int i = 0; i < 16; i++)
    {
        matrix_copy[i] = matrix[i];
    }

    float scale_matrix[16] = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1};

    multiply(matrix_copy, scale_matrix, matrix);
}
