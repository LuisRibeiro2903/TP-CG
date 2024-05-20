#ifndef LIGHTPOINT_HPP
#define LIGHTPOINT_HPP

#include "light.hpp"

class LightPoint : public Light {
    private:
        float posX, posY, posZ;

    public:
        LightPoint(float posX, float posY, float posZ);
        void applyLight() override;
};

#endif