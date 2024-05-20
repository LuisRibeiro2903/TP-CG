#ifndef LIGHTDIR_HPP
#define LIGHTDIR_HPP

#include <GL/glew.h>

#include "light.hpp"

class LightDir : public Light {
    private:
        float dirX, dirY, dirZ;

    public:
        LightDir(float dirX, float dirY, float dirZ, int lightId)
            : Light(lightId), dirX(dirX), dirY(dirY), dirZ(dirZ) {};

            
        void applyLight() override;
};

#endif