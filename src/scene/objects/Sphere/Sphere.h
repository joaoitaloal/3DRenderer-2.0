#ifndef RENDERER_SPHERE_H
#define RENDERER_SPHERE_H

#include "../Shape.h"

//ToDo
class Sphere : public Shape{
    public:
        Sphere(Vector3R sphere_center, float radius);
        Collision get_collision(RayR ray) override;

    private:
        Vector3R sphere_center;
        float radius;
};

#endif // RENDERER_SPHERE_H