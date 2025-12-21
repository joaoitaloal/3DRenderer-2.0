#ifndef RENDERER_DIRECTIONALLIGHT_H
#define RENDERER_DIRECTIONALLIGHT_H

#include "../Light.h"

// ToDo
class DirectionalLight : public Light {
    public:
        // DirectionalLight();
        //Vector3 get_light_vector(Vector3 origin) {};

        // Ou change direction, só se sobrar tempo pra fz tbm:
        // void rotate_direction();
    private:
        Vector3R direction;
};

#endif // RENDERER_DIRECTIONALLIGHT_H