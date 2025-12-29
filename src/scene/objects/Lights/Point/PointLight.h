#ifndef RENDERER_POINTLIGHT_H
#define RENDERER_POINTLIGHT_H

#include "../Light.h"

class PointLight : public Light{
    public:
        PointLight(Vector3R position_, Color3 intensity_);

        Vector3R get_light_vector(Vector3R origin);

        // ToDo
        // void translate() override {};
    private:
        Vector3R position;
};

#endif // RENDERER_POINTLIGHT_H