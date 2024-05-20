#include "engine/lights/lightDir.hpp"


void LightDir::applyLight() {
    glLightfv(GL_LIGHT0 + lightID, GL_POSITION, new float[4]{dirX, dirY, dirZ, 0.0});
}