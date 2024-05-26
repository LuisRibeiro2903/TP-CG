#include "engine/transform/translate.hpp"
#include "cgmath.hpp"


Translate::Translate(float x, float y, float z) : x(x), y(y), z(z) {}

void Translate::applyTransform() { glTranslatef(x, y, z); }

void Translate::applyTransform(float *matrix)
{
    float matrix_copy[16];
    for (int i = 0; i < 16; i++)
    {
        matrix_copy[i] = matrix[i];
    }

    float translation_matrix[16] = {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };

    multiply(matrix_copy, translation_matrix, matrix);
}

