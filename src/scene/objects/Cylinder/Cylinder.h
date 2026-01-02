#ifndef RENDERER_CYLINDER_H
#define RENDERER_CYLINDER_H

#include "../Shape.h"

#include "../Circle/Circle.h"

//ToDo
class Cylinder : public Shape{
    public:
        Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_, Material3 material_);
        Collision get_collision(RayR ray) override;

        Cylinder* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;
        
        // Temporário, espero
        void update_radius(float radius_);
        void update_height(float height_);
    
    private:
        Vector3R base_center, axis_dir;
        float radius, height;

        MatrixR Q; // projection on axis_dir
        MatrixR M; // orthogonal projection on axis_dir

        Circle base;
        Circle roof;

        Collision get_surface_collision(RayR ray);

        void update_transformation_matrices() override;
};

#endif // RENDERER_CYLINDER_H