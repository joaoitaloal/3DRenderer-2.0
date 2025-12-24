#ifndef RENDERER_CIRCLE_H
#define RENDERER_CIRCLE_H

#include "../Plane/Plane.h"

// Circulo 2D, tipo o triangulo só que é um circulo
class Circle : public Plane {
    public:
        Circle(Vector3R point_, Vector3R normal_, float radius_, bool culled);
        Collision get_collision(RayR ray) override;

    private:
        float radius;
};

#endif // RENDERER_CIRCLE_H