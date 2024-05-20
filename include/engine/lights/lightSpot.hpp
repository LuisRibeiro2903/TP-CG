#ifndef LIGHTSPOT_HPP
#define LIGHTSPOT_HPP

#include "light.hpp"

#include <GL/glew.h>

class LightSpot : public Light {
    private:
        float posX, posY, posZ;
        float dirX, dirY, dirZ;
        float cutoff;

    public:
        LightSpot(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float cutoff, int lightID)
            : Light(lightID), posX(posX), posY(posY), posZ(posZ), dirX(dirX), dirY(dirY), dirZ(dirZ), cutoff(cutoff) {};
        void applyLight() override;
};

#endif