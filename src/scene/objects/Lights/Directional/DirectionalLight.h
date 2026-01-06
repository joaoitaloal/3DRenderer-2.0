#ifndef RENDERER_DIRECTIONALLIGHT_H
#define RENDERER_DIRECTIONALLIGHT_H

#include "../Light.h"

// TODO
class DirectionalLight : public Light {
    public:
        // DirectionalLight();
        //Vector3 get_light_vector(Vector3 origin) {};
        
    private:
        Vector3R direction;
};

#endif // RENDERER_DIRECTIONALLIGHT_H