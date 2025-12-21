#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H

#include "../../../math/Color3.h"
#include "../../../math/Vector3R.h"

// Luz genérica
class Light{
    public:
        // Retorna o vetor l
        virtual Vector3R get_light_vector(Vector3R origin) = 0;

        Color3 get_intensity() { return intensity; }
    protected:
        Color3 intensity;
};

#endif // RENDERER_LIGHT_H