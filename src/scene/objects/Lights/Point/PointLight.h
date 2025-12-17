#ifndef RENDERER_POINTLIGHT_H
#define RENDERER_POINTLIGHT_H

#include "../MovableLight.h"

// Lembrar de tirar esse include quando criarmos nossa classe de vetor
#include <raymath.h>

class PointLight : public MovableLight{
    public:
        PointLight(Vector3 position_, Color3 intensity_);

        Vector3 get_light_vector(Vector3 origin);

        // ToDo
        void translate() override {};
};

#endif // RENDERER_POINTLIGHT_H