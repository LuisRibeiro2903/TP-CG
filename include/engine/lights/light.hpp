#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "engine/color.hpp"

class Light {
    protected:
        int lightID;

    public:
        Light(int lightID) : lightID(lightID) {}

        virtual void applyLight() = 0;

        void initialize() {
            glEnable(GL_LIGHT0 + lightID);
            float white[] = {1.0, 1.0, 1.0, 1.0};
            glLightfv(GL_LIGHT0 + lightID, GL_DIFFUSE, white);
            glLightfv(GL_LIGHT0 + lightID, GL_SPECULAR, white);
        }
};

#endif
