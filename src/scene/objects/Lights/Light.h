#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H

#include <raylib.h>

#include "../../../math/Color3.h"

// Luz genérica
class Light{
    public:
        // Retorna o vetor l
        virtual Vector3 get_light_vector(Vector3 origin) = 0;

        Color3 get_intensity() { return intensity; }
    protected:
        Color3 intensity;
};

#endif // RENDERER_LIGHT_H