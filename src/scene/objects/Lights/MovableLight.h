#ifndef RENDERER_MOVABLELIGHT_H
#define RENDERER_MOVABLELIGHT_H

#include "./Light.h"
#include "../Transformable.h"

class MovableLight : public Light, public Translatable {
    public:
        Vector3 get_position() { return position; }
    protected:
        Vector3 position;
};

#endif // RENDERER_MOVABLELIGHT_H