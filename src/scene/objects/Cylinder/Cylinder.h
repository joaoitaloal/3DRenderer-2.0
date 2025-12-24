#ifndef RENDERER_CYLINDER_H
#define RENDERER_CYLINDER_H

#include "../Shape.h"

// Temporário enquanto não temos a classe matriz
#include <raymath.h>
#include "../Circle/Circle.h"

//ToDo
class Cylinder : public Shape{
    public:
        Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_);
        Collision get_collision(RayR ray) override;
    
    private:
        Vector3R base_center, axis_dir;
        float radius, height;

        Matrix Q; // projection on axis_dir
        Matrix M; // orthogonal projection on axis_dir

        Circle base;
        Circle roof;

        Collision get_surface_collision(RayR ray);
};

#endif // RENDERER_CYLINDER_H