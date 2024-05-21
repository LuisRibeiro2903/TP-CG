#include "engine/lights/lightSpot.hpp"

void LightSpot::applyLight() {
    float pos[4] = {posX, posY, posZ, 1.0};
    float dir[3] = {dirX, dirY, dirZ};

    glLightfv(GL_LIGHT0 + lightID, GL_POSITION, pos);
    glLightfv(GL_LIGHT0 + lightID, GL_SPOT_DIRECTION, dir);
    glLightf(GL_LIGHT0 + lightID, GL_SPOT_CUTOFF, cutoff);
}