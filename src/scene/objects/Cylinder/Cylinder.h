#ifndef RENDERER_CYLINDER_H
#define RENDERER_CYLINDER_H

#include "../Shape.h"

//ToDo
class Cylinder : public Shape{
    public:
        Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_);
        Collision get_collision(RayR ray) override;
    
    private:
        Vector3R base_center;
        Vector3R axis_dir;
        float radius;
        float height;
};

#endif // RENDERER_CYLINDER_H