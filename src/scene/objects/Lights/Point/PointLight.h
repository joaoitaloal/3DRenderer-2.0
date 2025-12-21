#ifndef RENDERER_POINTLIGHT_H
#define RENDERER_POINTLIGHT_H

#include "../MovableLight.h"

class PointLight : public MovableLight{
    public:
        PointLight(Vector3R position_, Color3 intensity_);

        Vector3R get_light_vector(Vector3R origin);

        // ToDo
        void translate() override {};
};

#endif // RENDERER_POINTLIGHT_H