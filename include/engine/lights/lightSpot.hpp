#ifndef LIGHTSPOT_HPP
#define LIGHTSPOT_HPP

#include "light.hpp"

class LightSpot : public Light {
    private:
        float posX, posY, posZ;
        float dirX, dirY, dirZ;
        float cutoff;

    public:
        LightSpot(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float cutoff, float exponent);
        void applyLight() override;
};

#endif