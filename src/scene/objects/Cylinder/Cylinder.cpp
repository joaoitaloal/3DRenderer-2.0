#include "Cylinder.h"

Cylinder::Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_){
    base_center = base_center_;
    axis_dir = axis_dir_;
    radius = radius_;
    height = height_;
}

Collision Cylinder::get_collision(RayR ray){
    Collision col;
    col.hit = false;


    
    return col;
}
