#ifndef RENDERER_SPHERE_H
#define RENDERER_SPHERE_H

#include "../Shape.h"

class Sphere : public Shape{
    public:
        Sphere(Vector3R sphere_center, float radius, Material3 material_, Textura* tex, string name_);
        Collision get_collision(RayR ray) override;

        Sphere* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;
        
        void set_radius(float radius_);

        void scale(Vector3R dims) override;

        void set_center(Vector3R pos);

    private:
        Vector3R sphere_center;
        float radius;

        void update_transformation_matrices() override;
};

#endif // RENDERER_SPHERE_H