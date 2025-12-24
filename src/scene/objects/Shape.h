#ifndef RENDERER_SHAPE_H
#define RENDERER_SHAPE_H

#include "./Material3.h"
#include "../../math/Vector3R.h"
#include "../../math/utils.h"

// Classe de forma genérica
class Shape{
    public:
        virtual Collision get_collision(RayR ray) = 0;

        // Retornando uma referencia read-only, nem sei se precisa, talvez copiar seria suave
        const Material3& get_material() const { return material; };

        virtual ~Shape() = default;

    protected:
        Material3 material;
};

#endif // RENDERER_SHAPE_H