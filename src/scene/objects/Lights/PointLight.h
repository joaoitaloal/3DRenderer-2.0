#ifndef RENDERER_POINTLIGHT_H
#define RENDERER_POINTLIGHT_H

#include "./Light.h"

class PointLight : public Light{
    public:
        PointLight(Vector3 position_, Color3 intensity_);

        // ToDo
        void translate() override {};
};

#endif // RENDERER_POINTLIGHT_H