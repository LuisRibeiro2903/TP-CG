#ifndef LIGHTPOINT_HPP
#define LIGHTPOINT_HPP

#include "light.hpp"

#include <GL/glew.h>


class LightPoint : public Light {
    private:
        float posX, posY, posZ;

    public:
        LightPoint(float posX, float posY, float posZ, int lightId)
        : Light(lightId), posX(posX), posY(posY), posZ(posZ) {};
        
        void applyLight() override;
};

#endif