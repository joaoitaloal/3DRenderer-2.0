#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H

#include <raylib.h>

#include "../../../math/Color3.h"
#include "../Transformable.h"

// Luz abstrata
class Light : public Translatable{
    public:
        Vector3 get_position() { return position; }

        Color3 get_intensity() { return intensity; }
    protected:
        Vector3 position;
        Color3 intensity;
};

#endif // RENDERER_LIGHT_H