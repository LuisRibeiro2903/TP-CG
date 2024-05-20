#include "engine/lights/lightPoint.hpp"

void LightPoint::applyLight() {
    glLightfv(GL_LIGHT0 + lightID, GL_POSITION, new float[4]{posX, posY, posZ, 1.0});
}