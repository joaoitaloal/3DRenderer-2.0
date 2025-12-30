#ifndef RENDERER_CONE_H
#define RENDERER_CONE_H

#include "../Shape.h"

#include "../Circle/Circle.h"

class Cone : public Shape{
    public:
        Cone(Vector3R base_center, Vector3R axis_dir, float radius, float height, Material3 material);
        Collision get_collision(RayR ray) override;

        Cone *transform_return(const MatrixR &m);
        void transform(const MatrixR& m) override;

    private:
        Vector3R base_center;
        Vector3R axis_dir;
        Vector3R vertice;

        MatrixR Q;
        MatrixR M;

        Circle base;

        float radius;
        float height;

        Material3 material;

        Collision get_surface_collision(RayR ray);
        
};

#endif // RENDERER_CONE_H